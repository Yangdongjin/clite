// token.hpp
// by David Weinman
// 7/22/13 10:15p

#ifndef TOKEN_H_
#define TOKEN_H_

struct Token {

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

	private:
		int KEYWORDS = tokenType.Eof.ordinal();
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

#endif /* TOKEN_H_ */

/*


        David Weinman
        The Evergreen State College / Computability and the study of Formal Languages
        Sheryl Shulman and Neal Nelson

NOTES:
        Skeleton code provided by Allen B. Tucker & Robert E. Noonan from Programming Languages Principles and Paradigms 2.ed


public class Token {

    private static final int KEYWORDS = TokenType.Eof.ordinal();

    private static final String[] reserved = new String[KEYWORDS];
    private static Token[] token = Token[KEYWORDS];

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

    private TokenType type;
    private String value = "";

    private Token (TokenType t, String v) {
        type = t;
        value = v;
        if (t.compareTo(TokenType.Eof) < 0) {
            int ti = t.ordinal();
            reserved[ti] = v;
    Token[ti] = this;
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
        return new Token(TokenType.Identifier, name);
    }

    public static Token mkIntLiteral (String name) {
        return new Token(TokenType.IntLiteral, name);
    }

    public static Token mkFloatLiteral (String name) {
        return new Token(TokenType.FloatLiteral, name);
    }

    public static Token mkCharLiteral (String name) {
        return new Token(TokenType.CharLiteral, name);
    }

    public String toString ( ) {
        if (type.compareTo(TokenType.Identifier) < 0) return value;
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
