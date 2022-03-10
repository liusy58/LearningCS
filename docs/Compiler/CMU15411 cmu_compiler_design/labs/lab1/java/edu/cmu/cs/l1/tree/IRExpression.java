// Mike Maxim
// ITTRee expression

package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.general.*;

public abstract class IRExpression extends Visitable {

    public void visit(Visitor v) {
	v.visitResponse(m_classname,this);
    }

    public String getClassName() {
	return m_classname;
    }

    public String toString() {
	return m_classname;
    }

    protected String m_classname;
}


