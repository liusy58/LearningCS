// Mike Maxim
// IRTree for seq

package edu.cmu.cs.l1.tree;

public class IRSeq extends IRStatement {

    public IRSeq(IRStatement l, IRStatement r) {
	m_left=l; m_right=r;

	m_classname = "IRSeq";
    }

    public IRStatement getLeft() {
	return m_left;
    }

    public IRStatement getRight() {
	return m_right;
    }

    private IRStatement m_left, m_right;
}


