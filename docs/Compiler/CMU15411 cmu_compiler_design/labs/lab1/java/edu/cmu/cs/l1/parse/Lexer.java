package edu.cmu.cs.l1.parse;

interface Lexer {
    public java_cup.runtime.Symbol nextToken() throws java.io.IOException;
}
