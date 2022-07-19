// Mike Maxim
// IRTree for labels

package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.temp.*;

public class IRLabel extends IRStatement {

    public IRLabel(Label l) {
	m_label = l;

	m_classname = "IRLabel";
    }

    public Label getLabel() {
	return m_label;
    }

    public String toString() {
	return "LABEL("+m_label.toString()+")";
    }

    private Label m_label;

}

