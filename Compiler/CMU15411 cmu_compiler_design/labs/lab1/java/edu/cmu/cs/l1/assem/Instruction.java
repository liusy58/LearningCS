// Mike Maxim
// Instruction representation

package edu.cmu.cs.l1.assem;

import java.util.*;
import edu.cmu.cs.l1.temp.*;

abstract public class Instruction {

    public abstract List sourceTemps();
    public abstract List destTemps();
    public abstract List labels();

    /* Get the String rep of the instruction */
    public String getInstruction() {
	return m_instr;
    }

    /** Format an instruction using a TempMap */
    public String format(TempMap map) {

	List dst = destTemps();
	List src = sourceTemps();
	List jumps = labels();

	StringBuffer fstr = new StringBuffer();
	int len = m_instr.length(),n;
	for (int i=0; i<len; i++) {
	    if (m_instr.charAt(i)=='`') {
		char nextChar = m_instr.charAt(++i);
		if (nextChar == 's') {
		    n = Character.digit(m_instr.charAt(++i),10);
		    fstr.append(map.tempMap((Temp)src.get(n)));
		}
		else if (nextChar == 'd') {
		    n = Character.digit(m_instr.charAt(++i),10);
		    fstr.append(map.tempMap((Temp)dst.get(n)));
		}
		else if (nextChar == 'j') {
		    n = Character.digit(m_instr.charAt(++i),10);
		    fstr.append(jumps.get(n).toString());
		}
		else if (nextChar == '`') {
		    fstr.append('`');
		}
		else {
		    throw new Error("bad Assem format");
		}
	    }
	    else {
		fstr.append(m_instr.charAt(i));
	    }
	}
	return fstr.toString();
    }

    protected String m_instr;
}
