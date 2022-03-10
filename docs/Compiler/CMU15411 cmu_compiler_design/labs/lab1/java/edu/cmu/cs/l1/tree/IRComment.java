package edu.cmu.cs.l1.tree;

public class IRComment extends IRStatement {

    public IRComment(String l) {
       m_comment = l;

       m_classname = "IRComment";
   }

   public String toString() {
       return m_comment;
   }


   private String m_comment;

}