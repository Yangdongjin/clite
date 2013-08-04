// lexer.hpp
// by David Weinman
// 7/25/13 11:00p

#ifndef LEXER_H_
#define LEXER_H_
#include <stdio.h>
#include <cstring>
#include "token.hpp"

struct Lexer {

	int isEof;
	char ch;
	int lineno;
	Token next();
	void error(char*);
	Lexer(char * filename);
	private:
		FILE * infh;
		int col;
		int lenLine;
		char nextChar();
		int isLetter(char);
		int isDigit(char);
		void check(char);
		Token chkOpt(char, Token, Token);
		char* concat(char*);

};

// ---- prototypes

int indexOf(char, char*);

// ---- constants

const int bufsize = 1024;
const char * letters = "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char * digits = "0123456789";
const char eolnCh = '\n';
const char eofCh = '\004';

// ---- variables

char * input;
char currentLine[bufsize];

// ---- def'ns

Lexer::Lexer(char * filename) {

	if ((infh = fopen(filename, "r")) == NULL) {
		printf("LEXERR: %s: %s", strerror(errno), filename);
		exit(1);
	} else if (fgets(input, bufsize, infh) == NULL) {
		printf("LEXERR: %s: %s", strerror(errno), filename);
		exit(1);
	} else {
		lenLine = snprintf(&currentLine, bufsize, "%s", input);
		ch = currentLine[0];
		lineno = 0;
		isEof = 0;
		col = 1;
	}

}

void Lexer::error(char * msg) {

	printf("LEXERR(%d): %s", lineno, msg);
	exit(1);

}

char Lexer::nextChar() {

	if (ch == eofCh) error("Attempt to read past end of file.");
	col++;
	if (col >= lenLine) {
		if (fgets(input, bufsize, infh) == NULL) {
			input = "" + eofTok.toString();
		} else {
			lineno++;
			input += '\n';
			snprintf(&currentLine, bufsize, input);
		}
		col = 0;
	}
	return currentLine[col];

}

int Lexer::isLetter(char c) {

	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

int Lexer::isDigit(char c) {

	return (c >= '0' && c <= '9');

}

void Lexer::check(char c) {
	char * errMsg;
	ch = nextChar();
	if (ch != c) {
		snprintf(errMsg, bufsize, "Illegal character, expecting: %c", c);
		error(errMsg);
	}
	ch = nextChar();

}

Token Lexer::chkOpt(char c, Token one, Token two) {

	ch = nextChar();
	if (ch == c) return two;
	return one;

}

char * Lexer::concat(char * set) {
	char setArry[bufsize];
	snprintf(setArry, bufsize, set);
	char * r = "";
	do {
		snprintf(r, bufsize, "%s%c", r, c);
		ch = nextChar();
	} while (indexOf(ch, setArry) >= 0)
	return r;

}

int indexOf(char c, char * string) {

	char arry[bufsize];
	int i = 0;
	snprintf(arry, bufsize, string);
	do {
		if (arry[i] == c) {
			return i;
		}
		i++;
	}
	snprintf(arry, bufsize, "indexOf couldn't find %c in %s.", c, string);
	error(&arry);

}

#endif /* LEXER_H_ */

/*
import java.io.*;

public class Lexer {

    private boolean isEof = false;
    private char ch = ' '; 
    private BufferedReader input;
    private String line = "";
    private int lineno = 0;
    private int col = 1;
    private final String letters = "abcdefghijklmnopqrstuvwxyz"
        + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private final String digits = "0123456789";
    private final char eolnCh = '\n';
    private final char eofCh = '\004';
    

    public Lexer (String fileName) { // source filename
        try {
            input = new BufferedReader (new FileReader(fileName));
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileName);
            System.exit(1);
        }
    }

    private char nextChar() { // Return next char
        if (ch == eofCh)
            error("Attempt to read past end of file");
        col++;
        if (col >= line.length()) {
            try {
                line = input.readLine( );
            } catch (IOException e) {
                System.err.println(e);
                System.exit(1);
            } // try
            if (line == null) // at end of file
                line = "" + eofCh;
            else {
                // System.out.println(lineno + ":\t" + line);
                lineno++;
                line += eolnCh;
            } // if line
            col = 0;
        } // if col
        return line.charAt(col);
    }
            

    public Token next( ) { // Return next token
        do {
            if (isLetter(ch)) { // ident or keyword
                String spelling = concat(letters + digits);
                return Token.keyword(spelling);
            } else if (isDigit(ch)) { // int or float literal
		// print ch
                String number = concat(digits);
                if (ch != '.')  // int Literal
                    return Token.mkIntLiteral(number);
                number += concat(digits);
                return Token.mkFloatLiteral(number);
            } else switch (ch) {
            case ' ': case '\t': case '\r': case eolnCh:
                ch = nextChar();
                break;
            
            case '/':  // divide or comment
                ch = nextChar();
                if (ch != '/')  return Token.divideTok;
                // comment
                do {
                    ch = nextChar();
                } while (ch != eolnCh);
                ch = nextChar();
                break;
            
            case '\'':  // char literal
                char ch1 = nextChar();
                nextChar(); // get '
                ch = nextChar();
                return Token.mkCharLiteral("" + ch1);
                
            case eofCh: return Token.eofTok;
            
            case '+': ch = nextChar();
                return Token.plusTok;
	    case '-': ch = nextChar();
		return Token.minusTok;
	    case '*': ch = nextChar();
		return Token.multiplyTok;
	    case '(': ch = nextChar();
		 return Token.leftParenTok;
	    case ')': ch = nextChar();
		 return Token.rightParenTok;
	    case '{': ch = nextChar();
		 return Token.leftBraceTok;
	    case '}': ch = nextChar();
		 return Token.rightBraceTok;
	    case ';': ch = nextChar();
		return Token.semicolonTok;
	    case ',': ch = nextChar();
		return Token.commaTok;
	    case '[': ch = nextChar();
		return Token.leftBracketTok;
	    case ']': ch = nextChar();
		return Token.rightBracketTok;

                // - * ( ) { } ; ,  student exercise
                
            case '&': check('&'); return Token.andTok;
            case '|': check('|'); return Token.orTok;

            case '=':
                return chkOpt('=', Token.assignTok,
                                   Token.eqeqTok);
	    case '<': ch = nextChar();
		return Token.ltTok;
	    case '>': ch = nextChar();
		return Token.gtTok;
	    case '!':
		return chkOpt('=', Token.notTok,
				   Token.noteqTok);
	  // a comment operator?
	  //  case '/':
	  //	return chkOpt('/',Token.divide ,
	  //			   Token.);
		//case 
                // < > !  student exercise 

            default:  error("Illegal character " + ch); 
            } // switch
        } while (true);
    } // next


    private boolean isLetter(char c) {
        return (c>='a' && c<='z' || c>='A' && c<='Z');
    }
  
    private boolean isDigit(char c) {
        return (c>= '0' && c<='9');  // student exercise
    }

    private void check(char c) {
        ch = nextChar();
        if (ch != c) 
            error("Illegal character, expecting " + c);
        ch = nextChar();
    }

    private Token chkOpt(char c, Token one, Token two) {
	ch = nextChar();
	if (ch == c) return two;
        return one;  // student exercise
    }

    private String concat(String set) {
        String r = "";
        do {
            r += ch;
            ch = nextChar();
        } while (set.indexOf(ch) >= 0);
        return r;
    }

    public void error (String msg) {
        System.err.print(line);
        System.err.println("Error: column " + col + " " + msg);
        System.exit(1);
    }

    static public void main ( String[] argv ) {
        Lexer lexer = new Lexer(argv[0]);
        Token tok = lexer.next( );
        while (tok != Token.eofTok) {
            System.out.println(tok.toString());
            tok = lexer.next( );
        } 
    } // main

}


*/
