// token.cpp
// by David Weinman
// 7/25/13 11:00p

#include "token.hpp"

// ---- prototypes

Token::Token(TokenType, char*);
TokenType Token::getType();
char* Token::getValue();
char * Token::toString();

int main(int, char**);
int equals(char *, char *);

// ---- def'ns

Token::Token(TokenType t, char * val) {

	type = t;
	value = val;
	if (t < TokenType::Eof) {
		reserved[t] = val;
		token[t] = this;
	}	

}

TokenType Token::getType() { return type; }

char* Token::getValue() { return value; }

char* Token::toString() { if (type < TokenType.Identifier) return value; return (char) type + '\t' + value; }

int equals(char * str1, char * str2) {

	while (*str1 == *str2) {
		str1++;
		str2++;
		if ((*str1 == '\0') && (*str2 == '\0')) return 1;
	}
	return 0;

}

int main() {

	printf("\neofTok value: %d\n", eofTok);
	return 0;

}

/* HEADER

#ifndef TOKEN_H_
#define TOKEN_H_

enum TokenType {

	 Void, Bool, Char, Else, False, Float,
     If, Int, Main, True, While, Return,
     Eof, LeftBrace, RightBrace, LeftBracket, RightBracket,
     LeftParen, RightParen, Semicolon, Comma, Assign,
     Equals, Less, LessEqual, Greater, GreaterEqual,
     Not, NotEqual, Plus, Minus, Multiply,
     Divide, And, Or, Identifier, IntLiteral,
     FloatLiteral, CharLiteral

};

struct Token {

	TokenType getType();
	char* getValue();
	char* toString();

	private:
		char * reserved; //= new string of size KEYWORDS
		TokenType type;
		char * value;

};

// ---- prototypes

Token keyword(char *);
Token mkIdentTok(char *);
Token mkIntLiteral(char *);
Token mkFloatLiteral(char *);
Token mkCharLiteral(char *);

// ---- constants

const int KEYWORDS = Eof;
Token token[KEYWORDS];
Token eofTok = Token(Eof, "<<EOF>>");
Token boolTok = Token(Bool, "bool");
Token charTok = Token(Char, "char");
Token elseTok = Token(Else, "else");
Token falseTok = Token(False, "false");
Token floatTok = Token(Float, "float");
Token ifTok = Token(If, "if");
Token intTok = Token(Int, "int");
Token mainTok = Token(Main, "main");
Token trueTok = Token(True, "true");
Token whileTok = Token(While, "while");
Token leftBraceTok = Token(LeftBrace, "{");
Token rightBraceTok = Token(RightBrace, "}");
Token leftBracketTok = Token(LeftBracket, "[");
Token rightBracketTok = Token(RightBracket, "]");
Token leftParenTok = Token(LeftParen, "(");
Token rightParenTok = Token(RightParen, ")");
Token semicolonTok = Token(Semicolon, ";");
Token commaTok = Token(Comma, ",");
Token assignTok = Token(Assign, "=");
Token eqeqTok = Token(Equals, "==");
Token ltTok = Token(Less, "<");
Token lteqTok = Token(LessEqual, "<=");
Token gtTok = Token(Greater, ">");
Token gteqTok = Token(GreaterEqual, ">=");
Token notTok = Token(Not, "!");
Token noteqTok = Token(NotEqual, "!=");
Token plusTok = Token(Plus, "+");
Token minusTok = Token(Minus, "-");
Token multiplyTok = Token(Multiply, "*");
Token divideTok = Token(Divide, "/");
Token andTok = Token(And, "&&");
Token orTok = Token(Or, "||");
Token returnTok = Token(Return, "return");
Token voidTok = Token(Void, "void");

// ---- def'ns

Token keyword(char * name) {

	int i;
	char ch = *name;

	if (ch >= 'A' && ch <= 'Z') return mkIdentTok(name); 
	for (i = 0; i < KEYWORDS; i++) {
		if (equals(name, reserved[i])) return token[i];
	}
	return mkIdentTok(name);

}

Token mkIdentTok(char * name) { return Token(Identifier, name); }

Token mkIntLiteral(char * name) { return Token(IntLiteral, name); }

Token mkFloatLiteral(char * name) { return Token(FloatLiteral, name); }

Token mkCharLiteral(char * name) { return Token(CharLiteral, name); }

#endif / TOKEN_H_ /

*/
