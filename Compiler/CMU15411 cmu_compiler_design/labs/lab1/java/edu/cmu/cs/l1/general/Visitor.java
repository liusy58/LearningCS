// Mike Maxim
// Component of the Visitor pattern
// Visitor to classes that extend Visitable
package edu.cmu.cs.l1.general;

public interface Visitor {

    /** Respond to the visitee's request */
    public void visitResponse(String t, Object o);

}
