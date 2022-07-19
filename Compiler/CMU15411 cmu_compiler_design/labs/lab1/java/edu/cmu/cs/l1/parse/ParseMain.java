//Mike Maxim
//A utility to run the abstract syntax tree printer

package edu.cmu.cs.l1.parse;

import edu.cmu.cs.l1.absyn.*;
import java.io.*;
import edu.cmu.cs.l1.general.*;

/** A class for testing out the parser, for debugging purposes. */

public class ParseMain {

    public static void go(String cfile, String ofile) throws Exception {

        Parse p = new Parse();

        ASPrintAbsyn printer = new ASPrintAbsyn(System.out);

        try {
            p.parse(cfile);
        } catch (FileNotFoundException e) {
            System.out.println("PARSE: Error during parsing: Possibly a #include to a missing file in: " + ofile);
            Globals.shutdown(-1);
        }
        p.getProgram().visit(printer);

        System.out.println();
        Globals.shutdown(0);
    }
}


