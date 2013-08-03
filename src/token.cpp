// token.cpp
// by David Weinman
// 7/25/13 11:00p

#include "token.hpp"

// ---- prototypes

Token::Token(TokenType, char*);
TokenType Token::type();
char* Token::value();
Token Token::keyword(char *);
Token Token::mkIdentTok(char *);
Token Token::mkIntLiteral(char *);
Token Token::mkFloatLiteral(char *);
Token Token::mkCharLiteral(char *);
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

TokenType Token::type() { return type; }

char* Token::value() { return value; }

Token Token::keyword(char * name) {

	int i;
	char ch = *name;

	if (ch >= 'A' && ch <= 'Z') return mkIdentTok(name); 
	for (i = 0; i < KEYWORDS; i++) {
		if (equals(name, reserved[i])) return token[i];
	}
	return mkIdentTok(name);

}

Token Token::mkIdentTok(char * name) { return Token(TokenType.Identifier, name); }

Token Token::mkIntLiteral(char * name) { return Token(TokenType.IntLiteral, name); }

Token Token::mkFloatLiteral(char * name) { return Token(TokenType.FloatLiteral, name); }

Token Token::mkCharLiteral(char * name) { return Token(TokenType.CharLiteral, name); }

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

// token.hpp
// by David Weinman
// 7/22/13 10:15p

#ifndef TOKEN_H_
#define TOKEN_H_

struct Token {

	TokenType type();
	char* value();
	Token keyword(char *);
	Token mkIdentTok(char *);
	Token mkIntLiteral(char *);
	Token mkFloatLiteral(char *);
	Token mkCharLiteral(char *);
	char* toString();

	private:
		int KEYWORDS = tokenType.Eof; // tokenType.Eof returns the
					      // integer value of where the
					      // Eof token is in the enum
		char * reserved; //= new string of size KEYWORDS
		Token[] token = Token[KEYWORDS];
		TokenType type;
		char * value;

};

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

Token eofTok = Token(TokenType.Eof, "<<EOF>>");
Token boolTok = Token(TokenType.Bool, "bool");
Token charTok = Token(TokenType.Char, "char");
Token elseTok = Token(TokenType.Else, "else");
Token falseTok = Token(TokenType.False, "false");
Token floatTok = Token(TokenType.Float, "float");
Token ifTok = Token(TokenType.If, "if");
Token intTok = Token(TokenType.Int, "int");
Token mainTok = Token(TokenType.Main, "main");
Token trueTok = Token(TokenType.True, "true");
Token whileTok = Token(TokenType.While, "while");
Token leftBraceTok = Token(TokenType.LeftBrace, "{");
Token rightBraceTok = Token(TokenType.RightBrace, "}");
Token leftBracketTok = Token(TokenType.LeftBracket, "[");
Token rightBracketTok = Token(TokenType.RightBracket, "]");
Token leftParenTok = Token(TokenType.LeftParen, "(");
Token rightParenTok = Token(TokenType.RightParen, ")");
Token semicolonTok = Token(TokenType.Semicolon, ";");
Token commaTok = Token(TokenType.Comma, ",");
Token assignTok = Token(TokenType.Assign, "=");
Token eqeqTok = Token(TokenType.Equals, "==");
Token ltTok = Token(TokenType.Less, "<");
Token lteqTok = Token(TokenType.LessEqual, "<=");
Token gtTok = Token(TokenType.Greater, ">");
Token gteqTok = Token(TokenType.GreaterEqual, ">=");
Token notTok = Token(TokenType.Not, "!");
Token noteqTok = Token(TokenType.NotEqual, "!=");
Token plusTok = Token(TokenType.Plus, "+");
Token minusTok = Token(TokenType.Minus, "-");
Token multiplyTok = Token(TokenType.Multiply, "*");
Token divideTok = Token(TokenType.Divide, "/");
Token andTok = Token(TokenType.And, "&&");
Token orTok = Token(TokenType.Or, "||");
Token returnTok = Token(TokenType.Return, "return");
Token voidTok = Token(TokenType.Void, "void");

#endif / TOKEN_H_ /



    public static void main (String[] args) {
        System.out.println(eofTok.value);
        System.out.println(whileTok.value);
        System.out.println(returnTok.value);
        System.out.println(voidTok.value);
    }


*/
