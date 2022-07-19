//Mike Maxim
//Symbol table expception

package edu.cmu.cs.l1.symbol;

public class SymbolTableException extends Exception {

    public SymbolTableException() {
	super("SYMBTBL ERROR: Symbol Table Exception");
    }

    public SymbolTableException(String msg, Object base) {
	super("SYMBTBL ERROR: " + msg); m_base = base;
    }

    public Object getBase() {
	return m_base;
    }

    private Object m_base;
}