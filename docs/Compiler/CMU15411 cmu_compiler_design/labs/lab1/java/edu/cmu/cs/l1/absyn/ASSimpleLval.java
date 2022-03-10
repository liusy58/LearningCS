// Mike Maxim
// Absyn for simple variables

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.symbol.Symbol;

public class ASSimpleLval extends ASLval {

    /** Construct absyn for a simple variable
     * @param p Position in source
     * @param n The symbol representation of the variable name
     */
    public ASSimpleLval(int p, Symbol n) {
	super(p);
	m_name=n;

	m_classname = "ASSimpleLval";
    }

    /** Get the name of the variable */
    public Symbol getName() {
	return m_name;
    }

    /** Convert the variable to string form */
    public String toString() {
	return m_name.toString();
    }

    private Symbol m_name;
}
