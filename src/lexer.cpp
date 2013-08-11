// lexer.cpp
// by David Weinman
// 7/17/13 11:30p

#include "lexer.hpp"
#include "token.hpp"
#include <stdio.h>

// ---- prototypes

int main(int, char**);

// ---- def'ns

int main(int argc, char ** argv) {

	//printf("\neofTok value: %s\n", eofTok.toString());
	Lexer lexer = Lexer(*(++argv));
	lexer.next();
//	while (!lexer.isEof) {

		//printf("current token: %c\n", lexer.ch);
		//lexer.next();
	
//	}
	puts("done!");
	return 0;

}


/* *** lexer.hpp ***

#include "token.hpp"

struct Lexer {

	int isEof = 0;
	char ch = ' ';
	int lineno = 0;
	Token next();
	void error(char*);
	private:
		int col = 1;
		char nextChar();
		int isLetter(char);
		int isDigit(char);
		void check(char);
		Token chkOpt(char, Token, Token);
		char* concat(char*);

};

const char * letters = "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char * digits = "0123456789";
const char eolnCh = '\n';
const char eofCh = '\004';


*/

/* PSEUDO


*/


