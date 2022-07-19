// Mike Maxim
// OPER instruction

package edu.cmu.cs.l1.assem;

import java.util.*;

public class OperInstruction extends Instruction {

    public OperInstruction(String a, List d, List s, List j, boolean fallthrough) {
	m_instr=a; m_dst=d; m_src=s; m_jump=j; m_fallthrough=fallthrough;
    }
    public OperInstruction(String a, List d, List s) {
	m_instr=a; m_dst=d; m_src=s; m_jump=null; m_fallthrough=true;
    }

    public List sourceTemps() {
	return m_src;
    }
    public List destTemps() {
	return m_dst;
    }
    public List labels() {
	return m_jump;
    }
    public boolean jumpFallsThrough() {
        return m_fallthrough;
    }

    private List m_dst,m_src,m_jump;
    private boolean m_fallthrough;
}
