// Mike Maxim
// Absyn for integer expressions. Can being in many forms of ints

package edu.cmu.cs.l1.absyn;

public class ASIntConstant extends ASExpression {

    /** Construct the integer constant
     * @param p The position in the source
     * @param v Value of the int
     */
    public ASIntConstant(int p, int v) {
	super(p); m_value=v;
	m_classname = "ASIntConstant";
    }

    /** Construct an int with a String parameter
     * @param p Position in source
     * @param v String form of the number
     */
    public ASIntConstant(int p, String v) {
	super(p);

	m_classname = "ASIntConstant";

	if (v.equals("0")) {
	    m_value = 0;
	    return;
	}
        m_value = Integer.parseInt(v.substring(0,v.length()),10);
    }

    /** Return the value */
    public long getValue() {
	return m_value;
    }

    private long m_value;
}
