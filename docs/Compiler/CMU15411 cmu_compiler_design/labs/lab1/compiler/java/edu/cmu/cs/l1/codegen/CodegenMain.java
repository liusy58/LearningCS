//Mike Maxim
//Code generator test main file

package edu.cmu.cs.l1.codegen;

import edu.cmu.cs.l1.assem.*;
import edu.cmu.cs.l1.tree.*;
import edu.cmu.cs.l1.translate.*;
import java.util.*;
import edu.cmu.cs.l1.x86.*;
import edu.cmu.cs.l1.temp.*;

/** A class for testing out the code generator, for debugging purposes. */

public class CodegenMain {

  public static void go(String filename)  {

      StringBuffer code = new StringBuffer();
      String codeline = "";
      int i,j;

      /* Perform the (mostly) machine-independent part of compilation */
      Translator tr = new Translator();
      tr.translate(filename);

      CodeGenerator cg = new X86CodeGenerator();
      List asmcode = cg.codegen(tr.getProgram());

      // "Register Allocation"
      for (i = 0; i < asmcode.size(); i++) {
          codeline = ((Instruction)asmcode.get(i)).format(new DefaultMap());
          code.append(codeline);
      }

      System.out.println(code);
  }

}

