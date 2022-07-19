package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.temp.*;

public class IRName extends IRExpression {

    public IRName(String name) {
	m_label = new Label(name);
	m_classname = "IRName";
    }

    public IRName(Label lbl) {
        m_label = lbl;
	m_classname = "IRName";
    }

    public String getName() {
	return m_label.toString();
    }

    public Label getLabel() {
        return m_label;
    }

    private Label m_label;
}
