// Mike Maxim
// Component of the Visitor pattern
// Interface for objects able to be visited by certified Visitors

package edu.cmu.cs.l1.general;

public class Visitable {

    /** Dispatch the responce to the specified Visitor */
    public void visit(Visitor v) {
	v.visitResponse(m_classname,this);
    }

    protected String m_classname;
}
