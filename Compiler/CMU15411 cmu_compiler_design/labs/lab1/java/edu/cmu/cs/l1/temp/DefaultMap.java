//Mike Maxim

package edu.cmu.cs.l1.temp;

/** This class implements a default mapping of temps into Strings, which
    is useful mainly for debugging purposes.
*/
public class DefaultMap implements TempMap {
    public String tempMap(Temp t) {
        if (t == null) return "null";
        return t.toString();
    }

    public DefaultMap() {}
}

