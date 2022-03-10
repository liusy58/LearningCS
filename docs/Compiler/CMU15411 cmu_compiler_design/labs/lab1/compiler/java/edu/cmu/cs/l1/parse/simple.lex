package edu.cmu.cs.l1.parse;

import edu.cmu.cs.l1.errormsg.ErrorMsg;
import edu.cmu.cs.l1.general.*;
import java.util.*;

/**
  This file is used by JLex to create lexer.lex.java, which
  contains the Yylex class for lexical analysis.

  References: Appel, Chapter 2: Lexical Analysis
*/

%%

%implements Lexer
%function nextToken
%type java_cup.runtime.Symbol
%char

%state COMMENT
%state LINECOMMENT
 //%state FILENAME
 //%state CPPDESC

ALPHA=[A-Za-z_]
DIGIT=[0-9]
SPECIAL=[\*!@$%&\?\.\(\)\[\]\-\+\=/,<>:;\{\}\ ]
CTOKEN={ALPHA}|{DIGIT}|{SPECIAL}
WHITE_SPACE_CHAR=[\ \t\b\r\n]
NONNEWLINE_WHITE_SPACE_CHAR=[\r\ \t\b]
COMMENT_TEXT=([^/*\n]|[^*\n]"/"[^*\n]|[^*/\n]"*"[^*/\n]|"*"[^*/\n]|"/"[^*\n]|"*")
LINECOMMENT_TEXT=[^\n]

%{
private int comment_count = 0;
private boolean inlinecomment = false;

private void newline() {
  errorMsg.newline(yychar);
}

private void err(int pos, String s) {
  errorMsg.error(pos,s);
}

private void err(String s) {
  err(yychar,s);
}

private void outfile(String s) {
  if (!s.startsWith("<") && outputted.get(s) == null) {
    outputted.put(s, new Integer(1));
    Globals.verbosePrintln("  --- " + s);
  }
}

private java_cup.runtime.Symbol tok(int kind, Object value) {
    return new java_cup.runtime.Symbol(kind, yychar, yychar+yylength(), value);
}

private ErrorMsg errorMsg;
private int last_linenumber = 0;
private String filename = "";
private Hashtable outputted = new Hashtable();

Yylex(java.io.InputStream s, ErrorMsg e) {
  this(s);
  errorMsg=e;
}

%}

%eofval{
	{
	 return tok(sym.EOF, null);
        }
%eofval}       

%%

<YYINITIAL> \n { newline(); }
<YYINITIAL> {NONNEWLINE_WHITE_SPACE_CHAR} { }

<YYINITIAL> "{"  { return tok(sym.LBRACE, null); }
<YYINITIAL> "}"  { return tok(sym.RBRACE, null); }
<YYINITIAL> "("  { return tok(sym.LPAREN, null); }
<YYINITIAL> ")"  { return tok(sym.RPAREN, null); }
<YYINITIAL> "+"  { return tok(sym.PLUS, null); }
<YYINITIAL> "*"  { return tok(sym.TIMES, null); }
<YYINITIAL> "-"  { return tok(sym.MINUS, null); }
<YYINITIAL> "/"  { return tok(sym.DIVIDE, null); }
<YYINITIAL> "="  { return tok(sym.ASSIGN, null); }
<YYINITIAL> "%"  { return tok(sym.MOD, null); }
<YYINITIAL> "+=" { return tok(sym.PLUSASSIGN, null); }
<YYINITIAL> "*=" { return tok(sym.TIMESASSIGN, null); }
<YYINITIAL> "-=" { return tok(sym.MINUSASSIGN, null); }
<YYINITIAL> "/=" { return tok(sym.DIVIDEASSIGN, null); }
<YYINITIAL> "%=" { return tok(sym.MODASSIGN, null); }
<YYINITIAL> ";"  { return tok(sym.SEMICOL, null); }
<YYINITIAL> "return"  { return tok(sym.RETURN, null); }

<YYINITIAL> {DIGIT}+ { return tok(sym.INT, yytext()); }

<YYINITIAL> {ALPHA}({DIGIT}|{ALPHA})* { return tok(sym.ID, yytext()); }

<YYINITIAL> "//" { yybegin(LINECOMMENT); }
<YYINITIAL> "#"  { yybegin(LINECOMMENT); }
<LINECOMMENT> {LINECOMMENT_TEXT} { }
<LINECOMMENT> \n { newline(); yybegin(YYINITIAL); }

<YYINITIAL> "/*" { yybegin(COMMENT); comment_count = comment_count + 1; }
<COMMENT> "/*" { comment_count = comment_count + 1; }
<COMMENT> "*/" { 
	comment_count = comment_count - 1; 
	if (comment_count == 0) {
    		yybegin(YYINITIAL);
	}
}
<YYINITIAL> "*/" {
        err("Unbalanced comment");
}
<COMMENT> {COMMENT_TEXT} { }
<COMMENT> \n { newline(); }

<YYINITIAL,COMMENT,LINECOMMENT> . {
        err("Illegal character: <" + yytext() + ">");
}
