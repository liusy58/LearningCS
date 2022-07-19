// Mike Maxim
// IR printer

package edu.cmu.cs.l1.tree;

import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.temp.*;

public class IRPrint implements Visitor {

    java.io.PrintStream out;
    TempMap tmap;

    public IRPrint(java.io.PrintStream o, TempMap t) {
	out=o; tmap=t;
	indentLevel = 0;
    }

    public IRPrint(java.io.PrintStream o) {
	this(o, new DefaultMap());
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
        else if (type.equals("IRReturn")) {
            visitReturn(obj);
        }
	else if (type.equals("IRStatementList")) {
	    visitStmList(obj);
	}

    }

    private void visitReturn(Object r) {
        IRReturn ir = (IRReturn) r;

        indent();sayln("RETURN(");
        indentLevel++;
        ir.getExpression().visit(this);
        indentLevel--;
        indent(); sayln(")");

    }

    private void visitStmList(Object s) {

	IRStatementList as = (IRStatementList) s;
	int i;

	for (i = 0; i < as.getSize(); i++) {
	    as.getStatement(i).visit(this);
	    System.out.println();
	}

    }

    private void visitMove(Object s) {

	IRMove is = (IRMove) s;

	indent();sayln("MOVE(");
	indentLevel++;
        is.getDestination().visit(this);
	is.getSource().visit(this);
	indentLevel--;
        indent(); sayln(")");
    }

    private void visitSeq(Object s) {

	IRSeq is = (IRSeq) s;

	indent(); sayln("SEQ(");
	indentLevel++;
	is.getLeft().visit(this);
	if (is.getRight() != null) is.getRight().visit(this);
	indentLevel--;
        indent(); sayln(")");
    }

    private void visitLabel(Object l) {

	IRLabel il = (IRLabel) l;

	indent(); sayln("LABEL(");
        indentLevel++;
	indent(); sayln(il.getLabel().toString());
        indentLevel--;
        indent(); sayln(")");

    }

    private void visitComment(Object c) {

        IRComment ic = (IRComment) c;
        indent(); sayln("COMMENT(");
        indentLevel++;
        indent(); sayln(ic.toString());
        indentLevel--;
        indent(); sayln(")");
    }

    private void visitConst(Object e) {

	IRConst ie = (IRConst) e;

	indent(); sayln("CONST(");
        indentLevel++;
        indent(); sayln(String.valueOf(ie.getValue()));
        indentLevel--;
        indent(); sayln(")");
    }

    private void visitTemp(Object e) {

	IRTemp ie = (IRTemp) e;

	indent(); sayln("TEMP(");
        indentLevel++;
	indent(); sayln(tmap.tempMap(ie.getTemp()));
        indentLevel--;
        indent(); sayln(")");
    }

    private void visitBinop(Object e) {

	IRBinop ie = (IRBinop) e;

	indent(); sayln("BINOP(");
        indentLevel++;
        indent();
	switch(ie.getBinaryOperator()) {
	case IRBinop.PLUS: sayln("PLUS"); break;
	case IRBinop.MINUS: sayln("MINUS"); break;
	case IRBinop.MUL: sayln("MUL"); break;
	case IRBinop.DIV: sayln("DIV"); break;
	case IRBinop.MOD: sayln("MOD"); break;
	case IRBinop.AND: sayln("AND"); break;
	case IRBinop.OR: sayln("OR"); break;
	case IRBinop.XOR: sayln("XOR"); break;
	case IRBinop.NOT: sayln("NOT"); break;
        case IRBinop.BAND: sayln("BAND"); break;
        case IRBinop.BOR: sayln("BOR"); break;
        case IRBinop.BXOR: sayln("BXOR"); break;
        case IRBinop.LSHIFT: sayln("LSHIFT"); break;
        case IRBinop.RSHIFT: sayln("RSHIFT"); break;
	default:
	    System.out.println("IRPRINT: Warning Skipping Operator!");
	}
	indentLevel++;
	ie.getLeft().visit(this);
	ie.getRight().visit(this);
	indentLevel--; indentLevel--;
        indent(); sayln(")");
    }

    int indentLevel = 0;

    void indent(int d) {
	for(int i=0; i<d; i++) out.print(' ');
    }

    void indent() { indent(indentLevel); }

    void say(String s) { out.print(s); }

    void sayln(String s) { say(s); say("\n"); }
}

