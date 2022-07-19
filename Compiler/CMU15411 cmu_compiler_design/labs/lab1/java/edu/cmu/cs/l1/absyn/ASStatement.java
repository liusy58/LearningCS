// Mike Maxim
// Absyn for statements. This is the highest level of abstraction
// for statements.

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.general.*;

public class ASStatement extends Visitable {

    /** Construct the absyn statement
     * @param p Position in source
     */
    public ASStatement(int p) {
	m_pos = p;
	m_classname = "ASStatement";
    }

    /** Get the position */
    public int getPosition() {
	return m_pos;
    }

    /** Convert to string form */
    public String toString() {
	return m_classname;
    }

    protected int m_pos;

}
