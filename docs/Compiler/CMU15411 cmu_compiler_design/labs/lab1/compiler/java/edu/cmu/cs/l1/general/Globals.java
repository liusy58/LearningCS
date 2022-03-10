//Mike Maxim
//Global usefulness

package edu.cmu.cs.l1.general;

import java.io.*;

public class Globals {
    public Globals() {
    }

    public static boolean verboseCompilation = false;
    public static boolean underCygwin = false;

    public static void shutdown(int code) {
        System.exit(code);
    }

    public static void verbosePrint(String s) {
        if (verboseCompilation) {
            System.out.print(s);
        }
    }

    /** Print if verbose mode is on */
    public static void verbosePrintln(String s) {
        if (verboseCompilation) {
            System.out.println(s);
        }
    }

    /** For Cygwin external function calls */
    public static String extFunctionName(String f) {
        if (underCygwin)
            return "_" + f;
        return f;
    }
}