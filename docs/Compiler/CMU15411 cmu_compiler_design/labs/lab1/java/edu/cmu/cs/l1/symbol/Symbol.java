//Mike Maxim
//Interned symbols for quick comparisons and light storages

package edu.cmu.cs.l1.symbol;

/** Interned symbols, for representing identifiers in simple programs. */

public class Symbol {
    private String name;

    /** Construct the symbol from the string */
    private Symbol(String n) {
	name=n;
    }

    private static java.util.Dictionary dict = new java.util.Hashtable();

    /** Convert symbol to string */
    public String toString() {
	return name;
    }

    /** Determine if the string is in our intern table */
    public static boolean exists(String n) {

	String u = n.intern();
	Symbol s = (Symbol)dict.get(u);

	return (s != null);
    }

    /* Get the symbol object for the specified string */
    public static Symbol symbol(String n) {
	String u = n.intern();
	Symbol s = (Symbol)dict.get(u);
	if (s==null) {
	    s = new Symbol(u);
	    dict.put(u,s);
	}
	return s;
    }
}
