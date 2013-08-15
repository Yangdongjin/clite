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
	int i = 0;
	Lexer lexer = Lexer(*(++argv));
	lexer.next();
	while (!lexer.isEof || i++ >= 30) {

		printf("current token: %c\n", lexer.ch);
		lexer.next();
	
	}
	puts("done!");
	return 0;

}

/* OUT

2nextChar: input: int main() {
, currentLine: int main() {
 ch == eofCh: 0, ch: {, collumn: 12, lenLine: 32767, lineno: 0
currentLine[collumn] = current token:
LEXERR(0): Illegal character

*/


