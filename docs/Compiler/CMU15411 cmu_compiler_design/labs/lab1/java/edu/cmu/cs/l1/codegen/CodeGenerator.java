//Mike Maxim
//Interface for a code generator

package edu.cmu.cs.l1.codegen;

import java.util.*;
import edu.cmu.cs.l1.general.*;
import edu.cmu.cs.l1.tree.*;

public interface CodeGenerator {

    /** generate assem from a program */
    public List codegen(IRStatement code);

}