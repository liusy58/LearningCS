package edu.cmu.cs.l1.tree;

public class IRReturn extends IRStatement {
    public IRReturn(IRExpression expr) {
        m_exp = expr;
        m_classname = "IRReturn";
    }

    public IRExpression getExpression() {
        return m_exp;
    }

    private IRExpression m_exp;
}