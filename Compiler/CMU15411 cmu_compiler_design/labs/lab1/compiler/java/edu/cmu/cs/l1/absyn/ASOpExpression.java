//Mike Maxim
//Abstract syntax for expressions involving basic operators

package edu.cmu.cs.l1.absyn;

public class ASOpExpression extends ASExpression {

    /** Construct an expression from an operation
     * @param p Position in source
     * @param oper The operatoe being used
     * @param left The abstract syntax of the left side of the operation
     * @param right The abstract syntax of the right side of the operation
     */
    public ASOpExpression(int p, int oper, ASExpression left, ASExpression right) {
	super(p); m_oper = oper;
	m_left = left; m_right = right;

	m_classname = "ASOpExpression";
    }

    //Operator classes
    public static final int ARITH=0;

    // Arith
    public final static int PLUS=0, MINUS=1, MUL=2, DIV=3, MOD=4, NEG=5;

    /** Return the left side of the expression */
    public ASExpression getLeft() {
	return m_left;
    }

    /** Return the right side of the expression */
    public ASExpression getRight() {
	return m_right;
    }

    /** Return the operator */
    public int getOperator() {
	return m_oper;
    }

    /** Return the operator class */
    public int getOperatorClass() {
	if (m_oper >= ASOpExpression.PLUS && m_oper <= ASOpExpression.NEG) {
	    return ASOpExpression.ARITH;
	}
        return -1;
    }

    private int m_oper;
    private ASExpression m_left, m_right;
}