// Mike Maxim
// IRTree for statement

package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.general.*;

abstract public class IRStatement extends Visitable {

    public void visit(Visitor v) {
	v.visitResponse(m_classname, this);
    }

    public String getClassName() {
	return m_classname;
    }

    public String toString() {
	return m_classname;
    }

    protected String m_classname;
}


