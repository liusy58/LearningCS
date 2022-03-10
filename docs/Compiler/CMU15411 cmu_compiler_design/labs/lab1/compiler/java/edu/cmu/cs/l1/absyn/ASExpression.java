// Mike Maxim
// Absyn for expressions. Highest level of abstraction for expressions

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.general.*;

public class ASExpression extends Visitable {

    /** Construct the basics for the expression
     * @param p Position in source
     */

    public ASExpression(int p) {
	m_pos = p;
	m_classname = "ASExpression";
    }

    /** Return the position */
    public int getPosition() {
	return m_pos;
    }

    /** Convert to String form */
    public String toString() {
	return "ASExpression";
    }

    protected int m_pos;

}
