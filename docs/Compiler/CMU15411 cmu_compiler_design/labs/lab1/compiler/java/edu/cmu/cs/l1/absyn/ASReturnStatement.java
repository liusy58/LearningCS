//Mike Maxim
//Absyn for a return statement

package edu.cmu.cs.l1.absyn;

public class ASReturnStatement extends ASStatement {

    /** Construct a return statement using the expression
     * @param p Position in source
     * @param rexp The expression in the return statement
     */
    public ASReturnStatement(int p, ASExpression rexp) {
	super(p); m_rexp = rexp;

	m_classname = "ASReturnStatement";
    }

    /** Return the return statement expression */
    public ASExpression getReturnExpression() {
	return m_rexp;
    }

    /** Does the return statement even have an expression? */
    public boolean hasReturnExpression() {
	return (m_rexp != null);
    }

    private ASExpression m_rexp;
}