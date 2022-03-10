// Mike Maxim
// Absyn for statement lists

package edu.cmu.cs.l1.absyn;

import java.util.*;

public class ASStatementList extends ASStatement {

    /** Construct a blank statement list
     * @param p Position in source
     */
    public ASStatementList(int p) {
	super(p);
	m_classname = "ASStatementList";
    }
    /** Construct a statement list with a single element
     * @param p Position in source
     * @param d The head element
     */
    public ASStatementList(int p, ASStatement d) {
	super(p);
	m_decs.addElement(d);

	m_classname = "ASStatementList";
    }

    /** Get statement x */
    public ASStatement getStatement(int index) {
	return (ASStatement)m_decs.elementAt(index);
    }

    /** Get the number of elements in the list */
    public int getSize() {
	return m_decs.size();
    }

    /** Prepend an element to the list (non-imperative, does not change list)
     * @param d The element to prepend
     */
    public ASStatementList prepend(ASStatement d) {

	int i;
	ASStatementList dl = new ASStatementList(d.getPosition());

	dl.m_decs.addElement(d);
	for (i = 0; i < m_decs.size(); i++)
	    dl.m_decs.addElement(m_decs.elementAt(i));

	return dl;
    }

    /** Append a parameter to the end of the list
     * @param d The element to append
     */
    public ASStatementList append(ASStatement d) {
       ASStatementList dl = new ASStatementList(d.getPosition(), d);
       return join(dl);
    }

    /** Remove the head element from the list. Non-imperative, creates a new list */
    public ASStatementList removeFront() {

	int i;
	ASStatementList dl = new ASStatementList(m_pos);

	for (i = 1; i < m_decs.size(); i++)
	    dl.m_decs.addElement(m_decs.elementAt(i));

	return dl;
    }

    /** Remove the tail element from the list. Non-imperative, creates a new list */
    public ASStatementList removeBack() {
        int i;
        ASStatementList dl = new ASStatementList(m_pos);

        for (i = 0; i < m_decs.size()-1; i++)
            dl.m_decs.addElement(m_decs.elementAt(i));

        return dl;
    }

    /** Join two lists together
     * @param d The list to join, it will be in the back
     */
    public ASStatementList join(ASStatementList d) {

	int i;
	ASStatementList dl = new ASStatementList(m_pos);

	for (i = 0; i < m_decs.size(); i++)
	    dl.m_decs.addElement(m_decs.elementAt(i));

	for (i = 0; i < d.m_decs.size(); i++)
	    dl.m_decs.addElement(d.m_decs.elementAt(i));

	return dl;
    }

    /** Convert the list into string form */
    public String toString() {

	int i;
	String composite="";

	for (i = 0; i < m_decs.size(); i++)
	    composite += m_decs.elementAt(i).toString() + " ";

	return composite;
    }

    private Vector m_decs = new Vector();
}
