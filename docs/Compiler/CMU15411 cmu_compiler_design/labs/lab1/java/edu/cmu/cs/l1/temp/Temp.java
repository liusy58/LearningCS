//Mike Maxim
//A machine temporary

package edu.cmu.cs.l1.temp;

import java.util.*;

public class Temp  {

    //Global temp list
    public static List tempList = new ArrayList();
    private static int count=-1;
    public static int count() { return count; }

    private int num; //Temp id
    public Temp() { num=++count; tempList.add(this); }

    public String toString() { return "t" + num; }
    public int num() { return num; }

    public int hashCode() {
        return num;
    }
}
