// Mike Maxim
// IRTree rep for constants

package edu.cmu.cs.l1.tree;

public class IRConst extends IRExpression {

    public IRConst(long v) {
	m_value=v;

	m_classname = "IRConst";
    }

    public long getValue() {
	return m_value;
    }

    private long m_value;
}


