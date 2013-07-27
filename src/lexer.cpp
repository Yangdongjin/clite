// lexer.cpp
// by David Weinman
// 7/17/13 11:30p

#include "lexer.hpp"

/* *** lexer.hpp ***

struct lexer {

        lexer(char * filename);
        Token next();
        void error(char *);
        void main(char *);

        private:
                static bool isEof = false;
                static char ch = ' ';
                static char[] line = "";
                int lineno = 0;
                int col = 1;
                char[] letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                char[] digits = "0123456789";
                char eolnCh = '\n';
                char eofCh = '\004';
                char nextChar();
                bool isLetter(char);
                bool isDigit(char);
                void check(char);
                Token checkOpt(char, Token, Token);
                char * concat(String);

};

*/

Lexer::Lexer(char * filename) {

		// input = text in filename.

}

/* PSEUDO


*/


