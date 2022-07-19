// Mike Maxim
// IRTree for binops

package edu.cmu.cs.l1.tree;

public class IRBinop extends IRExpression {

    // Arith
    public final static int PLUS=0, MINUS=1, MUL=2, DIV=3, MOD=4;
    // Bitwise
    public final static int LSHIFT=35,RSHIFT=36,BOR=37,BAND=38,BXOR=39;
    // Bool Op
    public final static int AND=10,OR=11,XOR=12, NOT=13;

    public IRBinop(int b, IRExpression l, IRExpression r) {
	m_binop=b; m_left=l; m_right=r;

	m_classname = "IRBinop";
    }

    public int getBinaryOperator() {
	return m_binop;
    }

    public IRExpression getLeft() {
	return m_left;
    }

    public IRExpression getRight() {
	return m_right;
    }

    private int m_binop;
    private IRExpression m_left, m_right;
}


