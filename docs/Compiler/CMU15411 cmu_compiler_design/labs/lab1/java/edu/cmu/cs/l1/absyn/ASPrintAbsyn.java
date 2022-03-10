// Mike Maxim
// Absyn tree printer. Fulfils the role of visitor in the Visitor pattern
// scheme

package edu.cmu.cs.l1.absyn;

import edu.cmu.cs.l1.general.*;
import java.util.List;
import edu.cmu.cs.l1.symbol.Symbol;

public class ASPrintAbsyn implements Visitor {

    java.io.PrintStream out;

    /** Build the printer
     * @param o Specify the output stream for the printer
     */
    public ASPrintAbsyn(java.io.PrintStream o) {
        out = o;
        indentLevel = 0;
    }

    /** Dispatch various visitor handlers depending on the type of obj
     * @param type The String type of the class
     * @param obj The object itself
     */
    public void visitResponse(String type, Object obj) {

        if (type.equals("ASSimpleLval")) {
            visitSimpleVar(obj);
        }
        else if (type.equals("ASIntConstant")) {
            visitIntConstant(obj);
        }
        else if (type.equals("ASLvalExpression")) {
            visitVarExp(obj);
        }
        else if (type.equals("ASAssignStatement")) {
            visitAssign(obj);
        }
        else if (type.equals("ASStatementList")) {
            visitStmList(obj);
        }
        else if (type.equals("ASOpExpression")) {
            visitOpExp(obj);
        }
        else if (type.equals("ASReturnStatement")) {
            visitReturn(obj);
        }
        else {
            System.out.println(
                "Severe Internal Compiler Warning: Visit passing unknown visitable!: " +
                type);
        }
    }

    /** Print out the return absyn */
    private void visitReturn(Object r) {

        ASReturnStatement ar = (ASReturnStatement) r;

        indent(); sayln("Return(");
        indentLevel++;
        if (ar.hasReturnExpression()) {
            ar.getReturnExpression().visit(this);
        }
        indentLevel--;
        indent(); sayln(")");
    }

    /** Print out the simple variable */
    private void visitSimpleVar(Object v) {
        ASSimpleLval av = (ASSimpleLval) v;

        indent(); say("Lval(");
        say(av.getName().toString());
        sayln(")");
    }

    /** Print out the integer constant */
    private void visitIntConstant(Object i) {

        ASIntConstant ai = (ASIntConstant) i;

        indent(); say("Const(");
        say( (int) ai.getValue());
        sayln(")");
    }

    /** Print out the operation expression */
    private void visitOpExp(Object e) {

        ASOpExpression ai = (ASOpExpression) e;

        indent(); say("OpExp(");
        switch (ai.getOperator()) {
            case ASOpExpression.PLUS:
                say("PLUS");
                break;
            case ASOpExpression.MINUS:
                say("MINUS");
                break;
            case ASOpExpression.MUL:
                say("MUL");
                break;
            case ASOpExpression.DIV:
                say("DIV");
                break;
            case ASOpExpression.MOD:
                say("MOD");
                break;
            case ASOpExpression.NEG:
                say("UMINUS");
                break;
            default:
                throw new Error("Unknown Op");
        }
        sayln(",");
        indentLevel++;
        ai.getLeft().visit(this);

        if (ai.getRight() != null) {
            ai.getRight().visit(this);
        }
        indentLevel--;
        indent(); sayln(")");
    }

    /** Print out the variable expression */
    private void visitVarExp(Object v) {

        ASLvalExpression av = (ASLvalExpression) v;

        indent(); sayln("VarExp(");
        indentLevel++;
        av.getVariable().visit(this);
        indentLevel--;
        indent(); sayln(")");
    }

    /** Print out the assignment statement absyn */
    private void visitAssign(Object s) {

        ASAssignStatement as = (ASAssignStatement) s;

        indent(); sayln("Assign(");
        indentLevel++;
        as.getVariable().visit(this);
        as.getExpression().visit(this);
        indentLevel--;
        indent(); sayln(")");
    }

    /** Print out a statement list */
    private void visitStmList(Object ss) {

        int i;
        ASStatementList adl = (ASStatementList) ss;

        indent(); say("StmList(");
        if (adl != null) {
            sayln("");
            indentLevel++;

            for (i = 0; i < adl.getSize(); i++) {
                adl.getStatement(i).visit(this);
            }

            indentLevel--;
        }
        indent(); sayln(")");
    }

    void indent() {
        for (int i = 0; i < indentLevel; i++)
            out.print(' ');
    }

    void indent(int d) {
        for (int i = 0; i < d; i++)
            out.print(' ');
    }

    void say(boolean b) {
        Boolean local = new Boolean(b);
        out.print(local.toString());
    }

    void say(String s) {
        out.print(s);
    }

    void say(int i) {
        Integer local = new Integer(i);
        out.print(local.toString());
    }

    void sayln(String s) {
        say(s);
        say("\n");
    }

    int indentLevel = 0;
}