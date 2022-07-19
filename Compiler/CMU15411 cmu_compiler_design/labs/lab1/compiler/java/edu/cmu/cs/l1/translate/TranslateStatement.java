// Mike Maxim
// Statement translator

package edu.cmu.cs.l1.translate;

import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.absyn.*;
import edu.cmu.cs.l1.symbol.*;
import edu.cmu.cs.l1.temp.Temp;
import java.util.*;
import edu.cmu.cs.l1.errormsg.*;
import edu.cmu.cs.l1.tree.*;
import edu.cmu.cs.l1.temp.*;

public class TranslateStatement extends Translate {

    public TranslateStatement(ErrorMsg e, TranslateEnvironment t) {
	super(e,t);
    }

    public IRStatement getStatement() {
        return m_stm;
    }

    public void visitResponse(String type, Object obj) {

        int pos=0;

        if (obj instanceof ASStatement) {
            pos = ((ASStatement)obj).getPosition();
        }
        else if (obj instanceof ASExpression) {
            pos = ((ASExpression)obj).getPosition();
        }
        else if (obj instanceof ASLval) {
            pos = ((ASLval)obj).getPosition();
        }

        try {
            if (type.equals("ASAssignStatement")) {
                visitAssign(obj);
            }
            else if (type.equals("ASStatementList")) {
                visitStmList(obj);
            }
            else if (type.equals("ASReturnStatement")) {
                visitReturn(obj);
            }
            else {
                System.out.println("INTERNAL COMPILER ERROR: Skipping: " + type);
            }
        } catch (Exception e) {

            m_errorMsg.error(pos,"TRANSLATE: " + e.getMessage());
            System.exit(-1);
        }

    }

    /** Visit a return */
    private void visitReturn(Object o) {

        ASReturnStatement ao = (ASReturnStatement) o;
        IRStatement presult;

        TranslateExpression retran = new TranslateExpression(m_errorMsg, m_table);
        ao.getReturnExpression().visit(retran);
        m_stm = new IRReturn(retran.asExpression());
    }

    /** Visit an assign */
    private void visitAssign(Object s) throws TranslateException, SymbolTableException {

	ASAssignStatement as = (ASAssignStatement) s;

	TranslateExpression rhs = new TranslateExpression(m_errorMsg,m_table);
	TranslateVariable vhs = new TranslateVariable(m_errorMsg, m_table);
	as.getExpression().visit(rhs);

        ASSimpleLval var = (ASSimpleLval) as.getVariable();
        if (m_table.getEntry(var.getName()) == null)
            m_table.addEntry(var.getName(), new IRTemp(new Temp()));

        as.getVariable().visit(vhs);

        m_stm = new IRMove(vhs.getVariable(), rhs.asExpression());
    }

    /** Visit a stm list */
    private void visitStmList(Object s) {

	ASStatementList ss = (ASStatementList) s;

        if (ss.getSize() == 0) {
            m_stm = new IRLabel(new Label());
            return;
        }

	TranslateStatement h = new TranslateStatement(m_errorMsg, m_table);
	TranslateStatement t = new TranslateStatement(m_errorMsg, m_table);

	if (ss.getSize() > 1) {
	    ASStatementList tail = ss.removeFront();
	    ss.getStatement(0).visit(h);
	    tail.visit(t);
	    m_stm = new IRSeq(h.getStatement(), t.getStatement());
	}
	else {
	    ss.getStatement(0).visit(h);

	    m_stm = h.getStatement();
	}

    }

    private IRStatement m_stm;
    private static Stack m_donestack = new Stack(),m_teststack = new Stack();
}
