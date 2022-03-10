//Mike Maxim
//IR printter

package edu.cmu.cs.l1.translate;

/** A class for testing out the translator, for debugging purposes. */
import edu.cmu.cs.l1.x86.*;
import edu.cmu.cs.l1.tree.*;
import java.util.*;
import edu.cmu.cs.l1.general.*;

public class TranslateMain {

  public static void go(String filename)  {

      Translator t = new Translator();
      IRStatement code;

      t.translate(filename);
      int i;

      //Print the IR
      IRPrint printer = new IRPrint(System.out);
      code = t.getProgram();

      code.visit(printer);
      System.out.println();

      Globals.shutdown(0);
  }

}