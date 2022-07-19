// Mike Maxim
// Absyn for variables. Highest level of abstraction for variables

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.general.*;

public class ASLval extends Visitable {

    /** Construct the variable absyn
     * @param p Position in source
     */
    public ASLval(int p) {
	m_pos = p;

	m_classname = "ASLval";
    }

    /** Get position */
    public int getPosition() {
	return m_pos;
    }

    /** Convert to string form */
    public String toString() {
	return "ASLval";
    }

    protected int m_pos;

}
