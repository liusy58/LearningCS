//Mike Maxim
//Parser for L1 to create the absyn tree

package edu.cmu.cs.l1.parse;

import edu.cmu.cs.l1.absyn.*;
import java.io.*;
import edu.cmu.cs.l1.errormsg.*;

public class Parse {

    public Parse() {
    }

    /** Parse the file
     * @param filename The name of the file to parse
     */
    public void parse(String filename) throws FileNotFoundException {
        InputStream inp;

        m_errorMsg = new ErrorMsg(filename); //Create a new handler
        //Open the file
        inp=new FileInputStream(filename);

        //Create an instance of the CUP generated parser
        parser parser = new parser(new Yylex(inp,m_errorMsg), m_errorMsg);
        try {
            parser.parse(); //Parse
            m_parseResult = parser.parseResult;
        } catch (Throwable e) {
            //e.printStackTrace();
            //throw new Error(e.toString());
            System.out.println("Parse.java: parsing failed: " + e.toString());
            System.exit(-1);
        }
        try {
            inp.close();
        } catch (IOException e) {}

    }

    /** Get the absyn of the start of the program */
    public ASStatement getProgram() {
        return m_parseResult;
    }

    /** Get the handler that was augmented during parsing */
    public ErrorMsg getErrorHandler() {
        return m_errorMsg;
    }

    private ErrorMsg m_errorMsg;
    private ASStatement m_parseResult;
}


