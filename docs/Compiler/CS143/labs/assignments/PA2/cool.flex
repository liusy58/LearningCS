/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don"t remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

char * unmatched_block_comments = "Unmatched *)";
char * eof_in_string = "EOF in string constant";
char * eof_in_comment = "EOF in comment";
char * string_too_long = "String constant too long";
char * string_has_null = "String contains null character";
char * string_has_newline = "Unterminated string constant";


extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

%}

/*
 * Define names for regular expressions here.
 */

DARROW          =>
DIGIT           [0-9]
ALPHA           [a-zA-Z]
ALNUM           {ALPHA}|{DIGIT}
ASSIGN          <-
LE              <=




CLASS           [cC][lL][aA][sS][sS]
ELSE            [eE][lL][sS][eE]
FI              [fF][iI]
IF              [iI][fF]
IN              [iI][nN]
INHERIT         [iI][nN][hH][eE][rR][iI][tT]
ISVOID          [iI][sS][vV][oO][iI][dD]
LET             [lL][eE][tT]
LOOP            [lL][oO][oO][pP]
POOL            [pP][oO][oO][lL]
THEN            [tT][hH][eE][nN]
WHILE           [wW][hH][iI][lL][eE]
CASE            [cC][aA][sS][eE]
ESAC            [eE][sS][aA][cC]
NEW             [nN][eE][wW]
OF              [oO][fF]
NOT             [nN][oO][tT]
TRUE            true
FALSE           false

OPS             "+"|"/"|"-"|"*"|"="|"<"|"."|"~"|","|";"|":"|"("|")"|"@"|"{"|"}"
BLANK           "\t"|" "|"\f"|"\r"|"\t"|"\v"
LINECOMMENT     "--"
BLOCKCOMBEGIN   "(*"
BLOCKCOMEND     "*)"
NEWLINE         "\n"
TYPE            [A-Z][a-zA-Z0-9_]*
OBJECT          [a-z][a-zA-Z0-9_]*
INTCONST        [0-9]+
STRINGOP        \"

%Start LINE_COMMENT
%Start BLOCK_COMMENT
%Start STRING

%%

 /*
  *  Nested comments
  */


 /*
  *  The multiple-character operators.
  */


 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


<INITIAL>{BLOCKCOMBEGIN} {BEGIN(BLOCK_COMMENT);}
<BLOCK_COMMENT>{BLOCKCOMEND} {BEGIN(INITIAL);}
<BLOCK_COMMENT><<EOF>> {BEGIN(INITIAL);cool_yylval.error_msg = eof_in_comment;return ERROR;}


<INITIAL>{LINECOMMENT} {BEGIN(LINE_COMMENT);}
<LINE_COMMENT>{NEWLINE} {BEGIN(INITIAL);curr_lineno++;}

<BLOCK_COMMENT>{NEWLINE} {curr_lineno++;}
<BLOCK_COMMENT>. { }


<STRING>{STRINGOP} {BEGIN(INITIAL); *string_buf_ptr ='\0'; cool_yylval.symbol = inttable.add_string(strdup(string_buf));return STR_CONST;}
<STRING>{NEWLINE} {BEGIN(INITIAL);curr_lineno++;cool_yylval.error_msg = string_has_newline;return ERROR;}
<STRING><<EOF>> {BEGIN(INITIAL);cool_yylval.error_msg = eof_in_string;return ERROR;}

<STRING><<EOF>> {BEGIN(INITIAL);cool_yylval.error_msg = eof_in_string;return ERROR;}
<STRING>\\b {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
*string_buf_ptr++ = '\b';}
<STRING>\\t {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
*string_buf_ptr++ = '\t';}
<STRING>\\n {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
*string_buf_ptr++ = '\n';}
<STRING>\\f {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
*string_buf_ptr++ = '\f';}
<STRING>\\. {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
*string_buf_ptr++ = *(++yytext);}
<STRING>. {if(string_buf_ptr - string_buf >= MAX_STR_CONST-1){BEGIN(INITIAL);cool_yylval.error_msg = string_too_long;return ERROR;}
            *string_buf_ptr++ = *yytext;}




<INITIAL>{CLASS} {return (CLASS);}
<INITIAL>{ELSE} {return (ELSE);}
<INITIAL>{FI} {return (FI);}
<INITIAL>{IF} {return (IF);}
<INITIAL>{IN} {return (IN);}
<INITIAL>{INHERIT} {return (INHERITS);}
<INITIAL>{ISVOID} {return (ISVOID);}
<INITIAL>{LET} {return (LET);}
<INITIAL>{LOOP} {return (LOOP);}
<INITIAL>{POOL} {return (POOL);}
<INITIAL>{THEN} {return (THEN);}
<INITIAL>{WHILE} {return (WHILE);}
<INITIAL>{CASE} {return (CASE);}
<INITIAL>{ESAC} {return (ESAC);}
<INITIAL>{NEW} {return (NEW);}
<INITIAL>{OF} {return (OF);}
<INITIAL>{NOT} {return (NOT);}
<INITIAL>{TRUE}|{FALSE} {return BOOL_CONST;}
<INITIAL>{OPS} {return *yytext;}
<INITIAL>{BLANK} {}
<INITIAL>{NEWLINE} {curr_lineno++;}
<INITIAL>{DARROW} {return DARROW;}
<INITIAL>{ASSIGN} {return ASSIGN;}
<INITIAL>{LE} {return LE;}
<INITIAL>{TYPE} {cool_yylval.symbol = idtable.add_string(yytext); return TYPEID;}
<INITIAL>{OBJECT} {cool_yylval.symbol = idtable.add_string(yytext); return OBJECTID;}
<INITIAL>{INTCONST} {cool_yylval.symbol = inttable.add_string(yytext); return INT_CONST;}
<INITIAL>{STRINGOP} {string_buf_ptr = string_buf;BEGIN(STRING);}


<INITIAL>. {cool_yylval.error_msg = yytext; return ERROR;}



 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */

%%