// Mike Maxim
// Environment class

package edu.cmu.cs.l1.translate;

import edu.cmu.cs.l1.symbol.*;
import edu.cmu.cs.l1.tree.*;

public class TranslateEnvironment {

    public TranslateEnvironment() {
	m_env = new SymbolTable();
    }

    public void addEntry(Symbol name, IRExpression var) throws SymbolTableException {
	m_env.put(name,var);
    }

    public IRExpression getEntry(Symbol name) {
	return (IRExpression)m_env.get(name);
    }

    public void removeEntry(Symbol name) {
	m_env.remove(name);
    }

    public String toString() {
	String str="";
	str += m_env.toString() + "\n";
	return str;
    }

    private SymbolTable m_env;
}
