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
const char eolnCh = 10;
const char eofCh = 0;

// ---- variables

char * input;
char currentLine[bufsize];
char nextStr[bufsize];
char * concatStr;
int collumn;

// ---- def'ns

Lexer::Lexer(char * filename) {

	//puts("lexer constructer 1");
	if ((infh = fopen(filename, "r")) == NULL) {
		printf("l#62: LEXERR: %s: %s\n", strerror(errno), filename);
		exit(1);
	} else if (fgets(currentLine, bufsize, infh) == NULL) {
		input = currentLine;
		printf("l#66: LEXERR: %s: %s\n", strerror(errno), filename);
		//puts("lexer constructer 2");
		exit(1);
	} else {
		//puts("lexer constructer 2");
		input = (char *) &currentLine[0];
		printf("\nl#72: input: %s, currentLine: %s\n",((char *) input), ((char *) &currentLine));
		//puts("lexer constructer 3");
		ch = currentLine[0];
		//puts("lexer constructer 4");
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

	//printf("1addr of collumn: %p", &collumn);
	printf("\nl#93: 1nextChar(): input: %s, currentLine: %s ch == eofCh: %d, ch: %c, collumn: %d, lenLine: %d, lineno: %d\n", ((char *) input), ((char *) &currentLine), (ch == eofCh), ch, collumn++, lenLine, lineno);
	//printf("1addr of collumn: %p", &collumn);
	if (ch == eofCh) error((char *) "Attempt to read past end of file.");
	//puts("hi!1");
	//puts("hi!2");
	//printf("2addr of collumn: %p", &collumn); // seg fault 11
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
	//		printf("1addr of currentLine: %p, currentLine: %s", &currentLine, currentLine);
		//	printf("\n1addr of input: %p, input: %s\n\n", input, input);
			snprintf(currentLine, bufsize, "%s", input); // gdb said segfault occurs here
			//printf("2addr of currentLine: %p, currentLine: %s", &currentLine, currentLine);
		}
		collumn = 0;
	}
	printf("\nl#116: 2nextChar(): input: %s, currentLine: %s ch == eofCh: %d, ch: %c, collumn: %d, lenLine: %d, lineno: %d\n", ((char *) input), ((char *) &currentLine), (ch == eofCh), ch, collumn++, lenLine, lineno);
	//printf("3addr of collumn: %p", &collumn);
	printf("l#118: currentLine[collumn] = %c", currentLine[collumn]);
	return currentLine[collumn];

}

Token Lexer::next() {

	int i = 0;
	//input = &currentLine = ;

	do {
//		printf("\n%d (1) - c = %c\n", i, ch);
//		puts("lexer const 1");
		if (isLetter(ch)) {
//			puts("lexer const 2");
			snprintf(nextStr, bufsize, "%s%s", letters, digits);
			concatStr = nextStr;
//			puts("lexer const 6");
			char * spelling = concat(concatStr);
//			puts("lexer const 3");
			return keyword(spelling);
		} else if (isDigit(ch)) {
//			puts("lexer const 8");
			char * number = concat((char *) digits);
//			puts("lexer const 5");
			snprintf(nextStr, bufsize, "%s", number);
//			puts("lexer const 6");
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
				isEof = 1;
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
				puts("lexer next() [192]: case ch == ')' in switch");
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
				snprintf(errStr, bufsize, "l#242: Illegal character %c", ch);
				error((char *) errStr);

		} // switch
		//puts("lexer const 10");
		//printf("\n%d (2) - c = %c\n", i++, ch);
		//printf("(i < 10) : %d", (i < 10));

	} while (1);

} // next

int Lexer::isLetter(char c) {

	//puts("lexer isLetter1");

	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

int Lexer::isDigit(char c) {

	//puts("lexer isDigit1");

	return (c >= '0' && c <= '9');

}

void Lexer::check(char c) {

	char errMsg[bufsize];
	ch = nextChar();
	if (ch != c) {
		snprintf(errMsg, bufsize, "l#275:Illegal character, expecting: %c", c);
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
