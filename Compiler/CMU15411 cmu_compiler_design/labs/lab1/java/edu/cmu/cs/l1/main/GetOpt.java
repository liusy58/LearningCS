// Mike Maxim
// Class to support grabbing options from cmd line

package edu.cmu.cs.l1.main;

import java.util.*;

class Option {

    public String m_longname,m_shortname,m_description;
    public boolean m_data,m_required;
}

public class GetOpt {

    public GetOpt() {

    }

    public String getUsageHelp() {

	String str="";
	int i;

	Iterator opts = m_keytable.values().iterator();
	while (opts.hasNext()) {
	    Option opt = (Option) opts.next();

	    str += " -" + opt.m_shortname;
	    if (opt.m_data) {
		str += " " + "STR";
	    }
	    str += "\t--" + opt.m_longname;
	    if (opt.m_data) {
		str += "=STR";
	    }
	    str += "\t" + opt.m_description;
	    if (opt.m_required) {
		str += " (REQUIRED)";
	    }

	    str += "\n";
	}

	return str;
    }

    public void procCommandLine(String[] argv, int numnonopts) throws Exception {

	int i,nos=0;
	String curtoken,curdata;

	Iterator tokens = getTokenIterator(argv);
	m_nonopt = "";
	while (tokens.hasNext()) {
	    curtoken = (String) tokens.next();

	    if (curtoken.charAt(0) != '-') {
		m_nonopt += curtoken + " ";
		nos++;
	    }
	    else {

		curtoken = curtoken.substring(1);
		Enumeration reps = m_keytable.keys();
		boolean inserted = false;
		while (reps.hasMoreElements()) {
		    Integer key = (Integer) reps.nextElement();
		    Option rep = (Option) m_keytable.get(key);

		    if (("-"+rep.m_longname).equals(curtoken) || rep.m_shortname.equals(curtoken)) {
			inserted = true;
			if (rep.m_data) {
			    if (!tokens.hasNext()) {
				throw new Exception("Invalid Option");
			    }
			    curdata = (String) tokens.next();
			    m_datatable.put(key,curdata);
			}
			else {
			    m_datatable.put(key,"Blank");
			}
		    }
		}
		if (!inserted) {
		    throw new Exception("Unknown Option");
		}
	    }
	}

	m_nonopt = m_nonopt.trim();
	if (nos < numnonopts) {
	    throw new Exception("Missing Non Opts");
	}

	passOverReqedOpts();
    }

    private void passOverReqedOpts() throws Exception {

	Enumeration keys = m_keytable.keys();
	while (keys.hasMoreElements()) {
	    Integer curkey = (Integer) keys.nextElement();
	    if (((Option)m_keytable.get(curkey)).m_required &&
		m_datatable.get(curkey) == null) {
		throw new Exception("Missing required Option");
	    }
	}
    }

    private Iterator getTokenIterator(String[] argv) {
	int i;
	Vector v = new Vector();
	StringTokenizer kosherizer;

	for (i = 0; i < argv.length; i++) {
	    kosherizer = new StringTokenizer(argv[i],"=");
	    v.add(kosherizer.nextToken());
	    if (kosherizer.hasMoreTokens()) {
		v.add(kosherizer.nextToken());
	    }
	}

	return v.iterator();
    }

    public int regOption(String longrep, String shortrep, String description, boolean data, boolean required) {
	Option rep = new Option();

	rep.m_longname = longrep; rep.m_shortname = shortrep; rep.m_description = description;
	rep.m_data = data; rep.m_required = required;

	m_keytable.put(new Integer(m_nextKey),rep);

	return m_nextKey++;
    }

    public boolean getOption(int key) {
	return (m_datatable.get(new Integer(key)) != null);
    }

    public String getOptionData(int key) {
	return (String) m_datatable.get(new Integer(key));
    }

    public String getNonOptionArguments() {
	return m_nonopt;
    }

    private Hashtable m_keytable = new Hashtable(),m_datatable = new Hashtable();
    private String m_nonopt;
    private int m_nextKey=0;
}
