//Mike Maxim
//Main translator module

package edu.cmu.cs.l1.translate;

import edu.cmu.cs.l1.parse.Parse;
import edu.cmu.cs.l1.errormsg.ErrorMsg;
import edu.cmu.cs.l1.symbol.Symbol;
import edu.cmu.cs.l1.temp.*;
import edu.cmu.cs.l1.absyn.*;
import edu.cmu.cs.l1.tree.*;
import java.util.*;
import edu.cmu.cs.l1.general.*;

public class Translator {

    public Translator() {

    }

    public static final int DIVZERO=0;

    /** Produce IR code from a file */
    public void translate(String filename) {

	Parse parser = null;
	TranslateStatement progtran=null;
	IRStatement canonized=null;
        ErrorMsg errormsg=null;
        int i,errors;

	try {

	    parser = new Parse();

	    Globals.verbosePrintln("--- Initiating Translation Stage");
	    Globals.verbosePrintln(" --- Parsing");

            parser.parse(filename);
            errormsg = parser.getErrorHandler();

	    Globals.verbosePrintln(" --- Translating Abstract Syntax");
	    progtran = new TranslateStatement(errormsg,new TranslateEnvironment());
            parser.getProgram().visit(progtran);

            m_prog = progtran.getStatement();

            errors = progtran.getNumErrors();
            if (errors > 0) {
                System.out.println("("+errors+") errors. Compilation aborted.");
                System.exit(-1);
            }

	} catch (Exception e) {
	    e.printStackTrace();
	    System.out.println("Compilation aborted due to errors.");
	    System.exit(-1);
	}
    }

    public IRStatement getProgram() {
        return m_prog;
    }

    public static IRName getFileLabel(String file) {
        return (IRName) m_filemap.get(file);
    }

    public static IRName getErrorLabel(int type) {
        return (IRName) m_errormsgmap.get(new Integer(type));
    }

    private static IRStatement m_prog;
    private static Dictionary m_filemap = new Hashtable();
    private static Dictionary m_errormsgmap = new Hashtable();
}


