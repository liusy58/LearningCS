// Mike Maxim
// Absyn for variable expressions

package edu.cmu.cs.l1.absyn;

public class ASLvalExpression extends ASExpression {

    /** Construct a variable absyn with expression characteristics
     * @param p Position in source
     * @param v Variable
     */
    public ASLvalExpression(int p, ASLval v) {
	super(p);
	m_pos=p; m_var=v;

	m_classname = "ASLvalExpression";
    }

    /** Get the variable */
    public ASLval getVariable() {
	return m_var;
    }

    private ASLval m_var;
}
