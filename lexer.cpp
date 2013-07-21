// lexer.cpp
// by David Weinman
// 7/17/13 11:30p


struct lexer {

	lexer(string filename);
	Token next();
	void error(String);

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
		String concat(String);

	

};

lexer::lexer(string filename) {



}

/* PSEUDO


*/


