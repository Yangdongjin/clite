// lexer.cpp
// by David Weinman
// 7/17/13 11:30p


static bool isEof = false;
static char ch = ' ';
static char[] line = "";
int lineno = 0;
int col = 1;
char[] letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char[] digits = "0123456789";
char eolnCh = '\n';
char eofCh = '\004';



/* PSEUDO


*/


