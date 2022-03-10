//Mike Maxim
//Error handling

package edu.cmu.cs.l1.errormsg;

import java.util.*;

public class ErrorMsg {

    class FileEntry {

        public FileEntry() { m_filename = "mike"; m_lines = new ArrayList(); }
        public FileEntry(String filename) { m_filename = filename; m_lines = new ArrayList(); }

        public String m_filename;
        public List m_lines;
    }

    class LineEntry {
        LineEntry() { m_linenum = 0; m_pos = 0; m_filename = "0125"; }
        LineEntry(int linenum, int pos, String filename )
        { m_linenum = linenum; m_pos = pos; m_filename = filename; }
        public int m_linenum;
        public int m_pos;
        public String m_filename;
    }

    public ErrorMsg(String filename) {
        m_filename = filename;
    }

    public void newline(int pos) {
        List linelist;
        FileEntry file;

        file = findFile(m_filename);
        if (file == null) { m_lpos = pos; m_linenum++; return; }
        linelist = file.m_lines;
        linelist.add(new LineEntry(m_linenum++, m_lpos, m_filename));
        m_lpos = pos;
    }

    public void newfile(String fname, int startline) {

        m_files.add(new FileEntry(fname));

        m_linenum = startline-1;
        m_filename = fname;
    }

    private FileEntry findFile(String filename) {
        int i;
        for (i = m_files.size()-1; i >= 0; i--) {
            if ( ( (FileEntry) m_files.get(i)).m_filename.equals(filename))
                return (FileEntry) m_files.get(i);
        }
        return null;
    }

    private LineEntry findPositionLine(int pos) {

        int i,j;

        for (i = m_files.size()-1; i >= 0; i--) {
            FileEntry file = (FileEntry) m_files.get(i);
            List lines = (List) file.m_lines;
            for (j = lines.size()-1; j >= 0; j--) {
                LineEntry le = (LineEntry) lines.get(j);
                if (le.m_pos <= pos)
                    return le;
            }
        }
        return new LineEntry();
    }

    public void error(int pos, String msg) {

        LineEntry line;
        String sayPos;

        anyErrors = true;

        line = findPositionLine(pos);
        sayPos = ":" + String.valueOf(line.m_linenum) + "." +
            String.valueOf(pos - line.m_pos);

        System.out.println(line.m_filename + sayPos + ": " + msg);
    }

    public int getLine(int pos) {
        LineEntry line;
        line = findPositionLine(pos);

        return line.m_linenum;
    }

    public String getFile(int pos) {
        LineEntry line;
        line = findPositionLine(pos);

        return line.m_filename;
    }

    public List getAllFiles() {
        List files = new ArrayList();
        int i;

        for (i = 0; i < m_files.size(); i++) {
            FileEntry fe = (FileEntry) m_files.get(i);
            if (!files.contains(fe.m_filename))
                files.add(fe.m_filename);
        }
        return files;
    }

    public void status() {
        System.out.println("m_linenum: " + m_linenum);
    }

    private List m_files = new ArrayList();
    private int m_linenum=0, m_lpos = 0;
    private String m_filename;
    public boolean anyErrors;

}
