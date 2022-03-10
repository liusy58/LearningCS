//Mike Maxim
// ITTree stm lists

package edu.cmu.cs.l1.tree;

import java.util.*;

public class IRStatementList extends IRStatement {

    public IRStatementList() {
	m_classname = "IRStatementList";
    }
    public IRStatementList(IRStatement e) {
	m_exps.addElement(e);

	m_classname = "IRStatementList";
    }

    public IRStatementList(IRStatement s, IRStatementList l) {
	m_exps.add(s);
	if (l != null) {
	    m_exps.addAll(l.m_exps);
	}
	m_classname = "IRStatementList";
    }

    public IRStatementList(IRStatementList l) {
	m_exps.addAll(l.m_exps);

	m_classname = "IRStatementList";
    }

    public IRStatementList removeFront() {

	int i;
	IRStatementList dl = new IRStatementList();

	for (i = 1; i < m_exps.size(); i++) {
	    dl.m_exps.addElement(m_exps.elementAt(i));
	}
	return dl;
    }

    public int getSize() {
	return m_exps.size();
    }

    public IRStatement getStatement(int index) {
	return (IRStatement)m_exps.elementAt(index);
    }

    public IRStatementList prepend(IRStatement e) {

	int i;
	IRStatementList nl = new IRStatementList();

	nl.m_exps.addElement(e);
	for (i = 0; i < m_exps.size(); i++)
	    nl.m_exps.addElement(m_exps.elementAt(i));

	return nl;
    }

    public void append_imp(IRStatement s) {
	m_exps.add(s);
    }

    public IRStatementList append(IRStatement s) {

	IRStatementList nl = new IRStatementList();

	nl.m_exps.addAll(m_exps);
	nl.m_exps.add(s);

	return nl;
    }

    public IRStatementList join(IRStatementList l) {

	int i;
	IRStatementList nl = new IRStatementList();

	for (i = 0; i < m_exps.size(); i++)
	    nl.m_exps.addElement(m_exps.elementAt(i));

	for (i = 0; i < l.m_exps.size(); i++)
	    nl.m_exps.addElement(l.m_exps.elementAt(i));

	return nl;
    }

    private Vector m_exps = new Vector();
}
