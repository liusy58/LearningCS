// Mike Maxim
// x86 Code generator

package edu.cmu.cs.l1.x86;

import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.tree.*;
import edu.cmu.cs.l1.assem.*;
import java.util.*;
import edu.cmu.cs.l1.translate.*;
import edu.cmu.cs.l1.codegen.*;
import edu.cmu.cs.l1.temp.*;

public class X86CodeGenerator implements CodeGenerator, Visitor {

    public X86CodeGenerator() {
	m_instrs = new ArrayList();
    }

    public List codegen(IRStatement code) {

        code.visit(this);

        return m_instrs;
    }

    public void visitResponse(String type, Object obj) {

	if (type.equals("IRMove")) {
	    visitMove(obj);
	}
        else if (type.equals("IRComment"))
            visitComment(obj);
	else if (type.equals("IRSeq")) {
	    visitSeq(obj);
	}
        else if (type.equals("IRReturn")) {
            visitReturn(obj);
        }
	else if (type.equals("IRLabel")) {
	    visitLabel(obj);
	}
	else if (type.equals("IRConst")) {
	    visitConst(obj);
	}
	else if (type.equals("IRTemp")) {
	    visitTemp(obj);
	}
	else if (type.equals("IRBinop")) {
	    visitBinop(obj);
	}
	else if (type.equals("IRStatementList")) {
	    visitStmList(obj);
	}
        else if (type.equals("IRName")) {
            visitName(obj);
        }
        else {
            System.out.println("INTERNAL COMPILER ERROR: Skipping: " + type);
        }
    }

    private void visitReturn(Object r) {
        munchReturn((IRReturn)r);
    }

    private void visitName(Object n) {
        IRName in = (IRName) n;
        m_lastTemp = munchExp((IRName)in);
    }

    private void visitStmList(Object s) {

	IRStatementList as = (IRStatementList) s;
	int i;

	for (i = 0; i < as.getSize(); i++)  {
	    as.getStatement(i).visit(this);
	}
    }

    private void visitMove(Object s) {
	IRMove is = (IRMove)s;
        munchMove(is.getDestination(), is.getSource());

    }
    private void visitSeq(Object s) {
	IRSeq is = (IRSeq) s;
	munchSeq(is.getLeft(), is.getRight());
    }
    private void visitLabel(Object l) {
	IRLabel il = (IRLabel) l;
	munchLabel(il);
    }
    private void visitComment(Object c) {
        munchComment((IRComment)c);
    }

    private void munchReturn(IRReturn r) {
        Temp re = munchExp(r.getExpression());
        emit(new OperInstruction("\tRETURN\t`s0\n", null,  list(re)));
    }

    private void munchComment(IRComment c) {
        emit(new OperInstruction("\t\t\t\t\t/* " + c.toString() + " */\n", null, null));
    }

    private void munchLabel(IRLabel l) {
        emit(new LabelInstruction("." + l.getLabel().toString() + ":\n",l.getLabel()));
    }

    private Temp munchExp(IRName n) {
        Temp t = new Temp();
        emit(new MoveInstruction("\tMOVE\t" + n.getLabel() + "TO `d0\n", t, null, true));
        return t;
    }

    private void munchMove(IRExpression dst, IRExpression src) {

	Temp srctemp = munchExp(src);
        Temp dsttemp = munchExp(dst);
        move(srctemp,dsttemp,src,dst);

    }

    private void munchSeq(IRStatement left, IRStatement right) {
	left.visit(this);
	right.visit(this);
    }

    private void visitConst(Object e) {
	IRConst ie = (IRConst) e;
	m_lastTemp = munchExp(ie);
    }
    private void visitTemp(Object t) {
	IRTemp it = (IRTemp)t;
	m_lastTemp = munchExp(it);
    }
    private void visitBinop(Object e) {
	IRBinop ie = (IRBinop)e;
	m_lastTemp = munchExp(ie);
    }
    private Temp munchExp(IRExpression e) {
        Temp hit;
        if (null != (hit = (Temp) m_expmap.get(e)))
            return hit;
	e.visit(this);

        m_expmap.put(e, m_lastTemp);
	return m_lastTemp;
    }

    private Temp munchExp(IRTemp t) {
	return t.getTemp();
    }

    private Temp munchExp(IRConst n) {
	Temp r = new Temp();
	emit(new MoveInstruction("\tLOAD\t$"+(Integer.toString((int)n.getValue()))+" INTO `d0\n"
                                 ,r,null));

	return r;
    }

    private Temp munchExp (IRBinop e) {

	Temp r = new Temp();
	Temp lefttemp,righttemp;

	lefttemp = munchExp(e.getLeft());
	righttemp = munchExp(e.getRight());

	switch (e.getBinaryOperator()) {
	    case IRBinop.PLUS:
                emit(new OperInstruction("\tADD\t`s0 AND `s1 INTO `d0\n",
                                         list(r), list(lefttemp, righttemp)));

		break;
	    case IRBinop.MINUS:
                emit(new OperInstruction("\tSUBTRACT\t`s0 FROM `s1 INTO `d0\n", list(r),
                                                 list(righttemp, lefttemp)));
		break;
	    case IRBinop.MUL:
                emit(new OperInstruction("\tMULTIPLY\t`s0 BY `s1 INTO `d0\n", list(r),
                                                 list(lefttemp, righttemp)));
		break;
	    case IRBinop.DIV:
                emit(new OperInstruction("\tDIVIDE\t`s0 BY `s1 INTO `d0\n", list(r),
                                         list(lefttemp, righttemp)));
		break;
	    case IRBinop.MOD:
                emit(new OperInstruction("\tMOD\t`s0 BY `s1 INTO `d0\n", list(r),
                                         list(lefttemp, righttemp)));
                break;
	    default:
		throw new Error("Codegen.munchExp(BINOP)");
	}

	return r;
    }

    private List list(Object o, Object p) {
        List v = new ArrayList();
        v.add(o); v.add(p);
        return v;
    }

    private List list(Object o, Object p, Object q) {
        List v = new ArrayList();
        v.add(o); v.add(p); v.add(q);
        return v;
    }

    private List list(Object o) {
	List v = new ArrayList();
	v.add(o);
	return v;
    }

    private void emit(Instruction x) {
	m_instrs.add(x);
    }

    private void move(Temp srctemp, Temp dsttemp, IRExpression src, IRExpression dst) {
        emit(new MoveInstruction("\tMOVE\t`s0 INTO `d0\n",dsttemp,srctemp));
    }

    private Dictionary m_expmap = new Hashtable();
    private Temp m_lastTemp;
    private List m_instrs;
}
