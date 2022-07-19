// Mike Maxim
// Absyn for Assignment Statements

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.general.*;

public class ASAssignStatement extends ASStatement {

    /** Initialize the abstract syntax element
     * @param p Position of source code
     * @param v Variable being assigned into
     * @param e Expression to set the variable to
     */
    public ASAssignStatement(int p, ASLval v, ASExpression e) {
	super(p);
	m_var=v; m_exp=e;
	m_classname = "ASAssignStatement"; //Set for visitor pattern
    }

    /** Return the variable */
    public ASLval getVariable() {
	return m_var;
    }

    /** Return the expression */
    public ASExpression getExpression() {
        return m_exp;
    }

    /** Convert to a string */
    public String toString() {
	return "Assign: V: " + m_var.toString() + " E:" + m_exp.toString();
    }

    private ASLval m_var;
    private ASExpression m_exp;
}
