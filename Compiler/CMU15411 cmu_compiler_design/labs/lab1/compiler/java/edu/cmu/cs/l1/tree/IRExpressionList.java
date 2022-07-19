// Mike Maxim
// ITTree exp lists

package edu.cmu.cs.l1.tree;

import java.util.*;

public class IRExpressionList extends IRExpression {

    public IRExpressionList() {
        m_exps = new Vector();

	m_classname = "IRExpressionList";
    }
    public IRExpressionList(IRExpression e) {
	m_exps.addElement(e);

	m_classname = "IRExpressionList";
    }

    public IRExpressionList(IRExpression e, IRExpressionList ee) {
	m_exps.addElement(e);
	if (ee != null) {
	    m_exps.addAll(ee.m_exps);
	}

	m_classname = "IRExpressionList";
    }

    public IRExpressionList(IRExpressionList l) {
	m_exps.addAll(l.m_exps);

	m_classname = "IRExpressionList";
    }

    public int getSize() {
	return m_exps.size();
    }

    public IRExpression getExpression(int index) {
	return (IRExpression)m_exps.elementAt(index);
    }

    public IRExpressionList prepend(IRExpression e) {

	int i;
	IRExpressionList nl = new IRExpressionList();

	nl.m_exps.addElement(e);
	for (i = 0; i < m_exps.size(); i++) {
	    nl.m_exps.addElement(m_exps.elementAt(i));
	}

	return nl;
    }

    public IRExpressionList append(IRExpression e) {

        IRExpressionList l = new IRExpressionList(e);

        return this.join(l);
    }

    public IRExpressionList removeFront() {

	int i;
	IRExpressionList dl = new IRExpressionList();

	for (i = 1; i < m_exps.size(); i++) {
	    dl.m_exps.addElement(m_exps.elementAt(i));
	}
	return dl;
    }

    public IRExpressionList join(IRExpressionList l) {

	int i;
	IRExpressionList nl = new IRExpressionList();

	for (i = 0; i < m_exps.size(); i++) {
	    nl.m_exps.addElement(m_exps.elementAt(i));
	}
	for (i = 0; i < l.m_exps.size(); i++) {
	    nl.m_exps.addElement(l.m_exps.elementAt(i));
	}
	return nl;
    }

    private Vector m_exps = new Vector();
}



