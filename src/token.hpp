// token.hpp
// by David Weinman
// 7/22/13 10:15p

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

char * eofStr = "<<EOF>>";
char * boolStr = "bool";
char * charStr = "char";
char * elseStr = "else";
char * falseStr = "false";

const int KEYWORDS = Eof;
Token token[KEYWORDS];
Token eofTok = Token(Eof, eofStr);
Token boolTok = Token(Bool, boolStr);
Token charTok = Token(Char, charStr);
Token elseTok = Token(Else, elseStr);
Token falseTok = Token(False, falseStr);
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

#endif /* TOKEN_H_ */

/*

        David Weinman
        The Evergreen State College / Computability and the study of Formal Languages
        Sheryl Shulman and Neal Nelson

NOTES:
        Skeleton code provided by Allen B. Tucker & Robert E. Noonan from Programming Languages Principles and Paradigms 2.ed


public class Token {

    private static final int KEYWORDS = Eof.ordinal();

    private static final String[] reserved = new String[KEYWORDS];
    private static Token[] token = Token[KEYWORDS];

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

    private TokenType type;
    private String value = "";

    private Token (TokenType t, String v) {
        type = t;
        value = v;
        if (t.compareTo(Eof) < 0) {
            int ti = t.ordinal();
            reserved[ti] = v;
    	    token[ti] = this;
        }
    }

    public TokenType type( ) { return type; }

    public String value( ) { return value; }

    public static Token keyword  ( String name ) {
        char ch = name.charAt(0);
        
        if (ch >= 'A' && ch <= 'Z') return mkIdentTok(name);
        for (int i = 0; i < KEYWORDS; i++)
           if (name.equals(reserved[i])) return token[i];
        return mkIdentTok(name);
    } // keyword

    public static Token mkIdentTok (String name) {
        return new Token(Identifier, name);
    }

    public static Token mkIntLiteral (String name) {
        return new Token(IntLiteral, name);
    }

    public static Token mkFloatLiteral (String name) {
        return new Token(FloatLiteral, name);
    }

    public static Token mkCharLiteral (String name) {
        return new Token(CharLiteral, name);
    }

    public String toString ( ) {
        if (type.compareTo(Identifier) < 0) return value;
        return type + "\t" + value;
    } // toString

    public static void main (String[] args) {
        System.out.println(eofTok.value);
        System.out.println(whileTok.value);
        System.out.println(returnTok.value);
        System.out.println(voidTok.value);
    }
} // Token

*/
