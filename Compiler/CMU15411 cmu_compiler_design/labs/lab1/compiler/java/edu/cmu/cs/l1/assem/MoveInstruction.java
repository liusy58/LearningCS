// Mike Maxim
// Move instrution

package edu.cmu.cs.l1.assem;

import java.util.*;
import edu.cmu.cs.l1.temp.*;

public class MoveInstruction extends Instruction {

    public MoveInstruction(String a, Temp d, Temp s) {
	m_src = new ArrayList(); m_dst = new ArrayList();
        if (s != null) m_src.add(s);
        if (d != null) m_dst.add(d);
        m_instr=a;
        m_meminvolved = false;
    }

    /** Mem related keeps from being coalesced (later) */
    public MoveInstruction(String a, Temp d, Temp s, boolean mem) {
        this(a,d,s);
        m_meminvolved = mem;
    }

    public List sourceTemps() {
        return m_src;
    }

    public List destTemps() {
	return m_dst;
    }
    public List labels() {
	return null;
    }

    public void addSource(Temp t) {
        m_src.add(t);
    }

    public void setFormatSource(String o) {
        m_fsrc = o;
    }

    public void setFormatDest(String o) {
        m_fdst = o;
    }

    public boolean isMemRelated() {
        return m_meminvolved;
    }

    private String m_fsrc=null,m_fdst=null;
    private List m_dst;
    private List m_src;
    private boolean m_meminvolved=false;
}
