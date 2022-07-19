// Mike Maxim
// Imperative Symbol Table

package edu.cmu.cs.l1.symbol;

import java.util.*;

public class SymbolTable {

    public SymbolTable() {
    }

    /** Place a symbol in the table with the specified value */
    public void put(Symbol symbol, Object value) {
	m_table.put(symbol,value);
    }

    /** Get the value in the table corresponding to symbol */
    public Object get(Symbol symbol) {
	return m_table.get(symbol);
    }

    /** Remove a symbol */
    public void remove(Symbol symbol) {
        m_table.remove(symbol);
    }

    /** Convert the table to a string */
    public String toString() {
	return m_table.toString() + "\n";
    }

    private Hashtable m_table = new Hashtable();
}