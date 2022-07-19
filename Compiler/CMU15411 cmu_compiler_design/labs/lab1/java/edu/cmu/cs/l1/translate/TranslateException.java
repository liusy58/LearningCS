//Mike Maxim
//A translation errors

package edu.cmu.cs.l1.translate;

public class TranslateException extends Exception {

    public TranslateException() {
        super("Translation Error");
    }

    public TranslateException(String msg) {
        super("ERROR: " + msg);
    }
}
