// Mike Maxim
// Label instruction

package edu.cmu.cs.l1.assem;

import java.util.*;
import edu.cmu.cs.l1.temp.*;

public class LabelInstruction extends Instruction {

    public LabelInstruction(String a, Label l) {
        m_instr=a; m_label=l;
    }

    public List sourceTemps() {
        return null;
    }
    public List destTemps() {
        return null;
    }

    public List labels() {
        Vector l = new Vector();

	l.addElement(m_label);

	return l;
    }

    private Label m_label;
}

