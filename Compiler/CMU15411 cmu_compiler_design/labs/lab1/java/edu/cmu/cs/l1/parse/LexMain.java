package edu.cmu.cs.l1.parse;

import edu.cmu.cs.l1.errormsg.*;
/** A class for testing the lexer, for debugging purposes. */

public class LexMain {

  public static void main(String argv[]) throws java.io.IOException {
      String filename = argv[0];
      ErrorMsg errorMsg = new ErrorMsg(filename);
      java.io.InputStream inp=new java.io.FileInputStream(filename);
      Lexer lexer = new Yylex(inp,errorMsg);
      java_cup.runtime.Symbol tok;
      String token;

      do {
         tok=lexer.nextToken();
	 if (tok.value != null) token = symnames[tok.sym]+"("+tok.value+")";
	 else token = symnames[tok.sym];
	 errorMsg.error(tok.left, token);
      } while (tok.sym != sym.EOF);

      inp.close();
  }

  static String symnames[] = new String[100];
  static {

     symnames[sym.EOF] = "EOF";
     symnames[sym.LBRACE] = "LBRACE";
     symnames[sym.RBRACE] = "RBRACE";
     symnames[sym.LPAREN] = "LPAREN";
     symnames[sym.RPAREN] = "RPAREN";
     symnames[sym.PLUS] = "PLUS";
     symnames[sym.TIMES] = "TIMES";
     symnames[sym.MINUS] = "MINUS";
     symnames[sym.DIVIDE] = "DIVIDE";
     symnames[sym.MOD] = "MOD";
     symnames[sym.ASSIGN] = "ASSIGN";
     symnames[sym.PLUSASSIGN] = "PLUSASSIGN";
     symnames[sym.TIMESASSIGN] = "TIMESASSIGN";
     symnames[sym.MINUSASSIGN] = "MINUSASSIGN";
     symnames[sym.DIVIDEASSIGN] = "DIVIDEASSIGN";
     symnames[sym.MODASSIGN] = "MODASSIGN";
     symnames[sym.NEG] = "NEG";
     symnames[sym.SEMICOL] = "SEMICOL";
     symnames[sym.INT] = "INTEGER";
     symnames[sym.ID] = "ID";
   }

}


