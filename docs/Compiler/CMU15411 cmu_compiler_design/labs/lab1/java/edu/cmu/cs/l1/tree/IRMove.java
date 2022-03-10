// Mike Maxim
// IRTree rep for Move

package edu.cmu.cs.l1.tree;

public class IRMove extends IRStatement {

    public IRMove(IRExpression d, IRExpression s) {
	m_dst=d; m_src=s;

	m_classname = "IRMove";
    }

    public IRExpression getDestination() {
	return m_dst;
    }

    public IRExpression getSource() {
	return m_src;
    }

    public boolean isDestTemp() {
	return m_dst.getClassName().equals("IRTemp");
    }

    private IRExpression m_dst;
    private IRExpression m_src;
}


