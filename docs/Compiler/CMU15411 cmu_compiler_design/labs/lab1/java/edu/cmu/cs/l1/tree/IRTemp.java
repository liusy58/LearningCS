// Mike Maxim
// ITTree for temp

package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.temp.*;

public class IRTemp extends IRExpression {

    public IRTemp(Temp t) {
	m_temp=t;

	m_classname = "IRTemp";
    }

    public Temp getTemp() {
	return m_temp;
    }

    private Temp m_temp;
}


