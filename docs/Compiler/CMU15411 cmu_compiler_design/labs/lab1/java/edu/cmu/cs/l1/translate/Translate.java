//Mike Maxim
//Main translate visitor base class

package edu.cmu.cs.l1.translate;

import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.absyn.*;
import edu.cmu.cs.l1.errormsg.*;
import edu.cmu.cs.l1.tree.*;
import java.util.*;

public abstract class Translate implements Visitor {

    public Translate(ErrorMsg errormsg,
                     TranslateEnvironment table) {
        m_errorMsg = errormsg;
        m_table = table;
    }

    protected IRExpression allocInitExp() throws TranslateException {
      return new IRConst(0);
    }

    public int getNumErrors() {
        return m_numerrors;
    }

    /** Generic error */
    protected void error(int pos, String message) {
        m_errorMsg.error(pos, "TRANSLATE: " + message);
        m_numerrors++;
    }

    protected TranslateEnvironment m_table;
    protected ErrorMsg m_errorMsg;
    protected static int m_numerrors = 0;
}