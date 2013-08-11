// lexer.hpp
// by David Weinman
// 7/25/13 11:00p

#ifndef LEXER_H_
#define LEXER_H_
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
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
		int collumn;
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
char nextStr[bufsize];
char * concatStr;
int collumn;

// ---- def'ns

Lexer::Lexer(char * filename) {

	puts("lexer constructer 1");
	if ((infh = fopen(filename, "r")) == NULL) {
		printf("LEXERR: %s: %s\n", strerror(errno), filename);
		exit(1);
	} else if (fgets(currentLine, bufsize, infh) == NULL) {
		input = currentLine;
		printf("LEXERR: %s: %s\n", strerror(errno), filename);
		puts("lexer constructer 2");
		exit(1);
	} else {
		puts("lexer constructer 2");
		input = (char *) &currentLine[0];
		printf("\ninput: %s, currentLine: %s\n",((char *) input), ((char *) &currentLine));
		puts("lexer constructer 3");
		ch = currentLine[0];
		puts("lexer constructer 4");
		lineno = 0;
		isEof = 0;
		collumn = 1;
	}

} // Lexer

void Lexer::error(char * msg) {

	printf("LEXERR(%d): %s", lineno, msg);
	exit(1);

}

char Lexer::nextChar() {

	printf("1addr of collumn: %p", &collumn);
	printf("nextChar: input: %s, currentLine: %s ch == eofCh: %d, ch: %c, collumn: %d, lenLine: %d, lineno: %d\n", ((char *) input), ((char *) &currentLine), (ch == eofCh), ch, collumn++, lenLine, lineno);
	printf("1addr of collumn: %p", &collumn);
	if (ch == eofCh) error((char *) "Attempt to read past end of file.");
	puts("hi!1");
	puts("hi!2");
	printf("2addr of collumn: %p", &collumn); // seg fault 11
	if (collumn >= lenLine) {
		if (fgets(currentLine, bufsize, infh) == NULL) {
			input = currentLine;
			snprintf(nextStr, bufsize, "%s%s", input, eofTok.toString());
			input = nextStr;
		} else {
			lineno++;
			//input += '\n';
			snprintf(nextStr, bufsize, "%s", input);
			snprintf(input, bufsize, "%s\n", nextStr);
			printf("1addr of currentLine: %p, currentLine: %s", &currentLine, currentLine);
			printf("\n1addr of input: %p, input: %s\n\n", input, input);
			snprintf(currentLine, bufsize, "%s", input); // gdb said segfault occurs here
			printf("2addr of currentLine: %p, currentLine: %s", &currentLine, currentLine);
		}
		collumn = 0;
	}
	printf("3addr of collumn: %p", &collumn);
	printf("currentLine[collumn] = %c", currentLine[collumn]);
	return currentLine[collumn];

}

Token Lexer::next() {

	int i = 0;
	//input = &currentLine = ;

	do {
		printf("\n%d (1) - c = %c\n", i, ch);
		puts("lexer const 1");
		if (isLetter(ch)) {
			puts("lexer const 2");
			snprintf(nextStr, bufsize, "%s%s", letters, digits);
			concatStr = nextStr;
			puts("lexer const 6");
			char * spelling = concat(concatStr);
			puts("lexer const 3");
			return keyword(spelling);
		} else if (isDigit(ch)) {
			puts("lexer const 8");
			char * number = concat((char *) digits);
			puts("lexer const 5");
			snprintf(nextStr, bufsize, "%s", number);
			puts("lexer const 6");
			if (ch != '.') return mkIntLiteral(number);
			snprintf(nextStr, bufsize, "%s%s", number, digits);
			return mkFloatLiteral(nextStr);
		} else switch (ch) {

			case ' ': case '\t': case '\r': case eolnCh:
				ch = nextChar();
				break;

			case '/': // divide or comment
				ch = nextChar();
				if (ch != '/') return divideTok;
				// comment
				do {
					ch = nextChar();
				} while (ch != eolnCh);
				ch = nextChar();
				break;

			case '\'': // char literal
				char ch1;
				ch1 = nextChar();
				nextChar(); // get '
				ch = nextChar();
				return mkCharLiteral(&ch1);

			case eofCh:
				return eofTok;

			case '+':
				ch = nextChar();
				return plusTok;

			case '-':
				ch = nextChar();
				return minusTok;

			case '*':
				ch = nextChar();
				return multiplyTok;

			case '(':
				ch = nextChar();
				return leftParenTok;

			case ')':
				puts("lexer const 9");
				ch = nextChar();
				return rightParenTok;

			case '{':
				ch = nextChar();
				return leftBraceTok;

			case '}':
				ch = nextChar();
		 		return rightBraceTok;

			case ';':
				ch = nextChar();
				return semicolonTok;
			case ',':
	    		ch = nextChar();
				return commaTok;

			case '[':
				ch = nextChar();
				return leftBracketTok;

			case ']':
				ch = nextChar();
				return rightBracketTok;
                
            case '&': check('&');
        		return andTok;

            case '|': check('|');
            	return orTok;

            case '=':
                return chkOpt('=', assignTok,
                                   eqeqTok);
			case '<':
	    		ch = nextChar();
				return ltTok;

			case '>':
				ch = nextChar();
				return gtTok;

		    case '!':
				return chkOpt('=', notTok,
				   noteqTok);

			default:
				char errStr[bufsize];
				snprintf(errStr, bufsize, "Illegal character %c", ch);
				error((char *) errStr);

		} // switch
		puts("lexer const 10");
		printf("\n%d (2) - c = %c\n", i++, ch);
		printf("(i < 10) : %d", (i < 10));

	} while (i < 10);

} // next

int Lexer::isLetter(char c) {

	puts("lexer isLetter1");

	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

int Lexer::isDigit(char c) {

	puts("lexer isDigit1");

	return (c >= '0' && c <= '9');

}

void Lexer::check(char c) {

	char errMsg[bufsize];
	ch = nextChar();
	if (ch != c) {
		snprintf(errMsg, bufsize, "Illegal character, expecting: %c", c);
		error((char *) errMsg);
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
	char * r = (char*) "";
	snprintf(setArry, bufsize, "%s", set);
	do {
		snprintf(nextStr, bufsize, "%s%c", r, ch);
		r = nextStr;
		ch = nextChar();
	} while (indexOf(ch, setArry) >= 0);
	return r;

}

int indexOf(char c, char * string) {

	char arry[bufsize];
	int i = 0;
	snprintf(arry, bufsize, "%s", string);
	do {
		if (arry[i] == c) {
			return i;
		}
		i++;
	} while(arry[i] != '\0');
	return -1;

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
    private int collumn = 1;
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
        collumn++;
        if (collumn >= line.length()) {
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
            collumn = 0;
        } // if collumn
        return line.charAt(collumn);
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
		return Token.semicollumnonTok;
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
        System.err.println("Error: collumnumn " + collumn + " " + msg);
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


/* COPYPASTA

// below -- doesn't work
char Lexer::nextChar() {

	printf("nextChar, ch == eofCh: %d, ch: %c, collumn: %d, lenLine: %d, lineno: %d\n", (ch == eofCh), ch, collumn, lenLine, lineno);
	if (ch == eofCh) error((char *) "Attempt to read past end of file.");
	puts("hi!");
	printf("collumn + 1 : %d", (collumn + 1)); // seg fault: 11 here.
	if (++collumn >= lenLine) {
		if (fgets(currentLine, bufsize, infh) == NULL) {
			input = currentLine;
			snprintf(nextStr, bufsize, "%s%s", input, eofTok.toString());
			input = nextStr;
		} else {
			lineno++;
			input += '\n';
			snprintf(currentLine, bufsize, "%s", input);
		}
		collumn = 0;
	}
	printf("currentLine[collumn] = %c", currentLine[collumn]);
	return currentLine[collumn];

}
*/
