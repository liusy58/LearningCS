//Mike Maxim
//Main class for the full compilation

package edu.cmu.cs.l1.main;

import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.translate.*;
import edu.cmu.cs.l1.codegen.*;
import edu.cmu.cs.l1.x86.*;
import edu.cmu.cs.l1.temp.*;
import edu.cmu.cs.l1.assem.*;
import java.io.*;
import java.util.*;

public class Compiler {
    public Compiler() {
    }

    public static void go(String filename, String outfile) throws Exception {
        int i, j;
        StringBuffer code = new StringBuffer();

        Translator tr = new Translator();
        tr.translate(filename);

        CodeGenerator cg = new X86CodeGenerator();
        TempMap regalloc;

        Globals.verbosePrintln("\n--- Initiating Code Generation Stage");
        Globals.verbosePrintln(" --- Generating Code");
        List asmcode = cg.codegen(tr.getProgram());
        Globals.verbosePrintln(" --- Register Allocation");

        //The place where register allocation should take place
        regalloc = new DefaultMap();
        for (i = 0; i < asmcode.size(); i++) {
            Instruction ins = (Instruction) asmcode.get(i);
            code.append(ins.format(regalloc));
        }

        File ofile = new File(outfile); ofile.createNewFile();
        PrintStream targetfile = new PrintStream(new FileOutputStream(ofile));
        targetfile.print(code);

        Globals.verbosePrintln("--- Done.");

    }
}