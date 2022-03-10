//Mike Maxim
//A beat Pair class

package edu.cmu.cs.l1.general;

public class Pair {

    public Pair() {
    }

    public Pair(Object left, Object right) {
	m_left = left; m_right = right;
    }

    public Object getLeft() {
	return m_left;
    }

    public Object getRight() {
	return m_right;
    }

    private Object m_left,m_right;
}