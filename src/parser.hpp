// parser.hpp
// by David Weinman
// 7/21/13 10:00p

#ifndef PARSER_H_
#define PARSER_H_

class Parser {
  
  Token token;
  Lexer lexer;



};







#endif /* PARSER_H_ */




/*



        David Weinman
        The Evergreen State College / Computability and the study of Formal Languages
        Sheryl Shulman and Neal Nelson

NOTES:
        Skeleton code provided by Allen B. Tucker & Robert E. Noonan from Programming Languages Principles and Paradigms 2.ed


import java.util.*;
import java.util.Collections.*;

public class Parser {
    // Recursive descent parser that inputs a C++Lite program and 
    // generates its abstract syntax.  Each method corresponds to
    // a concrete syntax grammar rule, which appears as a comment
    // at the beginning of the method.
  
    Token token;          // current token from the input stream
    Lexer lexer;
  
    public Parser(Lexer ts) { // Open the C++Lite source program
        lexer = ts;                          // as a token stream, and
        token = lexer.next();            // retrieve its first Token
    }
  
    private String match (TokenType t) {
        String value = token.value();
        if (token.type().equals(t))
            token = lexer.next();
        else
            error(t);
        return value;
    }
  
    private void error(TokenType tok) {
        System.err.println("Syntax error @ line# " + lexer.lineno + ": expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }

    private void error(String tok) {
        System.err.println("Syntax error @ line# " + lexer.lineno + ": expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }
  
    public Program program() {
/

arrays are for data collection, old arrays are for swapping in order to increase array size.

/
      Declaration[ ] globals = new Declaration[0], globalsOld = new Declaration[0];
    	Function[ ] functions, functionsOld = new Function[0];
    	FunctionOrGlobal[ ] fOrG = new FunctionOrGlobal[0], fOrGO = new FunctionOrGlobal[0];
    	Function main = null;
    	int i = 0, j = 0, functionCtr = 0;
/

The following loop checks for types, a type can be followed by a function, main function
or global variable.

/
		//System.err.println("program()1 called token: " + token.value() + ".");
        while (isType()) {
        	Type t = type();
        	token = lexer.next();
            while (token.type().equals(TokenType.Identifier) || token.type().equals(TokenType.Main)) {
            	if (token.type().equals(TokenType.Main)) {
            		match(TokenType.Main);
            		match(TokenType.LeftParen);
            		match(TokenType.RightParen);
            		match(TokenType.LeftBrace);
            		Declarations mainLocals = declarations();
					Block mainBody = statements();
            		match(TokenType.RightBrace);
            		main = new Function(t, "main", new Declarations(new Declaration[0]), mainLocals, mainBody);
            	} else {
            	// here @ line 4.
            		fOrG = new FunctionOrGlobal[++i];
                	fOrG[i - 1] = functionOrGlobal(t);
                	System.arraycopy(fOrGO, 0, fOrG, 0, fOrGO.length);
                	fOrGO = new FunctionOrGlobal[i];
                	System.arraycopy(fOrG, 0, fOrGO, 0, fOrG.length);
                }
            }
        }
        //System.err.println("program()9 called token: " + token.value() + ". fOrG[" + fOrG.length + "].");
        i = 0;
// check for array index errors?
        while (i < fOrG.length) {
            if (fOrG[i].function != null) {
            	//System.err.println("program()11 called token: " + token.value() + ".");
            	functions = new Function[++functionCtr];
            	functions[functionCtr - 1] = fOrG[i++].function;
            	System.arraycopy(functionsOld, 0, functions, 0, functionsOld.length);
            	functionsOld = new Function[functionCtr];
            	System.arraycopy(functions, 0, functionsOld, 0, functions.length);
            } else if (fOrG[i].globals != null) {
            	//System.err.println("program()12 called, i = " + i + ", fOrG[i].globals length: " + fOrG[i].globals.length() + " globals length = " + globals.length);
            	globals = new Declaration[globals.length + fOrG[i].globals.length()];
            	//System.err.println("program()13 called, i = " + i + ", fOrG length: " + fOrG.length + " globals length = " + globals.length);
            	for (j = 0; j < fOrG[i].globals.length(); j++) {globals[(globals.length - 1) - j] = fOrG[i].globals.arrayVer()[j];}
            	System.arraycopy(globalsOld, 0, globals, 0, globalsOld.length);
            	globalsOld = new Declaration[globals.length];
            	System.arraycopy(globals, 0, globalsOld, 0, globals.length);
            	i += 1;
            } else {
            	globals = new Declaration[globals.length + 1];
            	globals[globals.length - 1] = fOrG[i++].global;
            	System.arraycopy(globalsOld, 0, globals, 0, globalsOld.length);
            }
        }
        //System.err.println("program()13 called token: " + token.value() + ".");
        if (main == null) {throw new IllegalArgumentException("Syntax error - main function was not found.");}
        functions = new Function[++functionCtr];
        functions[functionCtr - 1] = main;
        System.arraycopy(functionsOld, 0, functions, 0, functionsOld.length);
        //System.err.println("program()14 called token: " + token.value() + ".");
        return new Program(new Declarations(globals), new Functions(functions));
    }

    public FunctionOrGlobal functionOrGlobal(Type t) {
    	String id = token.value();
    	token = lexer.next();
		if (token.type().equals(TokenType.LeftParen)) {
    		token = lexer.next();
    		//System.err.println("functionOrGlobal()2 called token: " + token.value() + ".");
    		Declaration[ ] pOld = new Declaration[0];
    		Function f;
    		Declaration[ ] params = new Declaration[0];
    		int i = 0;
    		while (isType()) {
            	params = new Declaration[++i];
            	Type pT = type();
            	token = lexer.next();
            	params[i - 1] = declaration(pT);
            	System.arraycopy(pOld, 0, params, 0, pOld.length);
            	pOld = new Declaration[i];
            	System.arraycopy(params, 0, pOld, 0, params.length);
            	if (token.type().equals(TokenType.Comma)) {match(TokenType.Comma);}
        	}
        	match(TokenType.RightParen);
        	match(TokenType.LeftBrace);
        	Declarations locals = declarations();
        	Block body = statements();
        	match(TokenType.RightBrace);
        	return new FunctionOrGlobal(new Function(t, id, new Declarations(params), locals, body));
        } else if (token.type().equals(TokenType.Semicolon) || token.type().equals(TokenType.Comma)) {// maybe it could be an = too.
			//System.err.println("functionOrGlobal()3 called token: " + token.value() + ".");
			int i = 1;
        	Declaration[ ] global = new Declaration[1], gOld = null;
        	global[0] = new Declaration(new Variable(id), t);
        	//System.err.println("functionOrGlobal()4 called token: " + token.value() + ".");
        	while (token.type().equals(TokenType.Comma)) {
        		//System.err.println("functionOrGlobal()5 called token: " + token.value() + ".");
        		gOld = new Declaration[global.length];
        		System.arraycopy(global, 0, gOld, 0, global.length);
        		global = new Declaration[++i];
        		token = lexer.next();
        		//System.err.println("functionOrGlobal()6 called token: " + token.value() + ".");
        		global[i - 1] = new Declaration(new Variable(match(TokenType.Identifier)), t);
        		System.arraycopy(gOld, 0, global, 0, gOld.length);
        	}
        	match(TokenType.Semicolon);
        	//System.err.println("functionOrGlobal()5 called token: " + token.value() + ". global[" + global.length + "]: " + global[0].var().toString());
        	return new FunctionOrGlobal(new Declarations(global));
        }
        throw new IllegalArgumentException("Parser functionOrGlobal is neither, called C(d)");
    }

// System.out.println("01 -> token: " + token.value() + ".");


    private Declarations declarations () {
//	System.err.println("declarations called token: " + token.value() + ".");
        // Declarations --> { Declaration }
        Declaration[ ] ds1 = new Declaration[0], ds2 = new Declaration[0];
        Type t = null;
        int i = 0;
        while (isType()) {
            ds1 = new Declaration[++i];
            if (i > 1) {System.arraycopy(ds2, 0, ds1, 0, ds2.length);}
            t = type();
            token = lexer.next();
            ds1[i - 1] = declaration(t);
            while (token.type().equals(TokenType.Comma)) {
                ds2 = new Declaration[i];
                System.arraycopy(ds1, 0, ds2, 0, i++);
                ds1 = new Declaration[i];
                System.arraycopy(ds2, 0, ds1, 0, (i - 1));
                token = lexer.next();
                ds1[i - 1] = declaration(t);
            }
			if (!token.type().equals(TokenType.Comma)) {
				ds2 = new Declaration[i];
				System.arraycopy(ds1, 0, ds2, 0, ds1.length);			
			}
        	match(TokenType.Semicolon);
        // THE FOLLOWING COMMENTED CODE IS FOR ASSIGNMENTS IN DECLS.
		//System.err.println("declarations called (after d1 call *nxt) token: " + token.value() + ".");
		//if (token.type().equals(TokenType.Equals)) {
			//System.err.println("decls call, assn. token: " + token.value() + ".");
		//	Assignment a = new Assignment(ds1[0].var(), expression());
		//	if (token.type().equals(TokenType.Identifier)) {token = lexer.next();}
		//}
    }
	if (ds1.length == 0) { return new Declarations(0);}
	//	int k;
	//	for (k = 0; k < ds1.length; k++) System.out.printf("\ndeclarations called, looking at decls: " + ds1[k].toString() + " in index#" + k + ".");
        return new Declarations(ds1);  // student exercise
    }
 
    private Declaration declaration (Type typeInput) {
        // Declaration  --> Type Identifier { , Identifier } ;
	//System.out.printf("\ndeclaration called token: " + token.value() + ". id will be of type: " + typeInput.toString() + ".\n");
	return new Declaration(new Variable(match(TokenType.Identifier)), typeInput);
    }
 
    private Type type () {
        // Type  -->  int | bool | float | char 
        Type t = null;
	if (token.type().equals(TokenType.Int)) {t = new Type("int");}
	else if (token.type().equals(TokenType.Bool)) {t = new Type("bool");}
	else if (token.type().equals(TokenType.Float)) {t = new Type("float");}
	else if (token.type().equals(TokenType.Char)) {t = new Type("char");}
    else if (token.type().equals(TokenType.Void)) {t = new Type("void");}
	else {error("int or bool or float or char or void");}
        return t;          
    }
  
    private Statement statement() {
        // Statement --> ; | Block | Assignment | IfStatement | WhileStatement | Return | Call
        Statement s = null;
        //System.out.println("Statement()01 -> token: " + token.value() + ".");
    if (token.type().equals(TokenType.Semicolon)) {//System.err.println("if 1 bgn"); 
		s = new Skip();
		token = lexer.next();
	}// null stmnt
	else if (token.type().equals(TokenType.LeftBrace)) {//System.err.println("if 2 bgn");
		token = lexer.next();
		s = statements();
		match(TokenType.RightBrace);
	} // new block
	else if (token.type().equals(TokenType.Return)) {
		token = lexer.next();
		s = new Return(expression());
		if (token.type().equals(TokenType.Semicolon)) token = lexer.next();
	}// return stmnt
	else if (token.type().equals(TokenType.Identifier)) {//System.err.println("if 3 bgn, token: " + token.value() + ".");
		String id = token.value();
		//System.out.println("Statement() id 1 -> token: " + token.value() + ".");
		token = lexer.next();
		if (token.type().equals(TokenType.LeftParen)) {// if there's a parenthesis in your assignment, it's a call.
			token = lexer.next();
			Expression[ ] e = new Expression[0], eOld = new Expression[0];
			int i = 0;
			while (!(token.type().equals(TokenType.Semicolon))) {
				e = new Expression[++i];
				System.arraycopy(eOld, 0, e, 0, eOld.length);
				e[i - 1] = expression();
				token = lexer.next(); // this should be skipping each colon, and finally it skips a rightParen
				eOld = new Expression[i];
				System.arraycopy(e, 0, eOld, 0, e.length);
			}
			//System.out.println("Statement() call 1 -> token: " + token.value() + ".");
			match(TokenType.Semicolon);
			//System.out.println("Statement() call 2 -> token: " + token.value() + ".");
			s = new CallStmnt(new Call(id, new Expressions(e))); // call part	
		} else
			s = assignment(id);
	}// assignment or call
	else if (token.type().equals(TokenType.If)) {
		s = ifStatement();
	}// if stmnt
	else if (token.type().equals(TokenType.While)) {//System.err.println("if 5 bgn");
		s = whileStatement();
	}// while stmnt
	else throw new IllegalArgumentException("should never reach here (statement() in parser )");
	//System.out.println("Statement()last -> token: " + token.value() + ".");
	if (token.type().equals(TokenType.Semicolon)) token = lexer.next();
	return s;
    }
  
    private Block statements () {
        // Block --> '{' Statements '}'
	// Statement --> ; | Block | Assignment | IfStatement | WhileStatement
    //System.out.println("statements() 01 -> token: " + token.value() + ".");
	Statement[ ] block1 = {statement()}, block2;
	while (isStatement()) {
		//System.out.println("Statements()1 -> token: " + token.value() + ".");
		Statement s = statement();
		block2 = new Statement[block1.length];
		System.arraycopy(block1, 0, block2, 0, block1.length);
		block1 = new Statement[block2.length + 1];
		System.arraycopy(block2, 0, block1, 0, (block1.length - 1));
		block1[block1.length - 1] = s;
	}
		//System.err.println("end statements, token: " + token.value() + ".");
        return new Block(block1);
    }

    private Assignment assignment (String inputStr) {
        // Assignment --> Identifier = Expression ;
	Variable v = null;
	Expression e = null;
	//System.err.println("assignment begin -- token: " + token.value() + ".");
		//
	v = new Variable(inputStr);
	//System.err.println("assignment() -> if 1 token: " + token.value() + ".");
	if (token.type().equals(TokenType.Assign))
		match(TokenType.Assign);
    //if (token.type().equals(TokenType.Identifier)) {System.err.println("if 3 token: " + token.value() + ".");} //e = assignment().source();}
	//System.err.println("assignment() -> if 2 token: " + token.value() + ".");
	e = expression();
	return new Assignment(v, e);  // student exercise
    }
  
    private Conditional ifStatement () {
        // IfStatement --> if ( Expression ) Statement [ else Statement ]
	Expression e = null;
	Block thenPart = null, elsePart = null;
	Conditional elif = null;
	//System.err.println("ifStatement01, token: " + token.value() + ".");
	match(TokenType.If);
	//System.err.println("ifStatement after decls2, token: " + token.value() + ".");
	match(TokenType.LeftParen);
	//System.err.println("ifStatement after decls3, token: " + token.value() + ".");
	e = expression();
	//System.err.println("ifStatement after decls4, token: " + token.value() + ".");
	match(TokenType.RightParen);
	if (token.type().equals(TokenType.LeftBrace)) {token = lexer.next(); thenPart = statements(); match(TokenType.RightBrace);}
	else {Statement[ ] thenStmnt = {statement()}; thenPart = new Block(thenStmnt);}
	if (token.type().equals(TokenType.Else)) {
		token = lexer.next();
		if (token.type().equals(TokenType.If)) { // elif
			elsePart = statements();
		} else {
			if (token.type().equals(TokenType.LeftBrace)) {token = lexer.next(); elsePart = statements(); match(TokenType.RightBrace);}
			else {
				Statement[ ] elseStmnt = {statement()};
				elsePart = new Block(elseStmnt);
			}
			//System.out.println("if statement Else part -> else {} after statements, token = " + token.value() + ".");
		}
		return new Conditional(e, thenPart, elsePart);
	}
        return new Conditional(e, thenPart);  // student exercise
    }
  
    private Loop whileStatement () {
        // WhileStatement --> while ( Expression ) Statement
	Expression e = null;
	Block s = null;
	match(TokenType.While);
	match(TokenType.LeftParen);
	e = expression();
	match(TokenType.RightParen);
	match(TokenType.LeftBrace);
	s = statements();
	match(TokenType.RightBrace);
        return new Loop(e, s);  // student exercise
  }

    private Expression expression () {
        // Expression --> Conjunction { || Conjunction }
//	System.err.println("begin expression, token " + token.value() + ".");
	Expression e = conjunction();
	while (token.type().equals(TokenType.Or)) {
		token = lexer.next();
		e = new Binary(new Operator("||"), e, conjunction());
//		System.err.println("[expression()] while loop after lexer.next()#2, next token: " + token.value() + ".");
	}
//	System.err.println("end expression, token: " + token.value() + ".");
        return e;  // student exercise
    }
  
    private Expression conjunction () {
        // Conjunction --> Equality { && Equality }
// equality
//	System.err.println("begin conjunction, token: " + token.value() + ".");
	Expression e = equality();
	//System.err.println("equality finished pre while loop token: " + token.value() + ".");
	while (token.type().equals(TokenType.And)) {
		//System.err.println("[conjunction()] while loop after while cond., token: " + token.value() + ".");
		token = lexer.next();
		//System.err.println("[conjunction()] while loop after lexer.next(), token: " + token.value() + ".");
		e = new Binary(new Operator("&&"), e, equality());
	}
	//System.out.println("end conjunction, token: " + token.value() + ".");
        return e;  // student exercise
    }
  
    private Expression equality () {
        // Equality --> Relation [ EquOp Relations ]
// relation, equOp
	//System.err.println("begin equality, token: " + token.value() + ".");
	Expression e = relation();
	//System.err.println("equality after relation(), token: " + token.value() + ".");
	while (isEqualityOp()) {
		//System.err.println("equality, after isEqualityOp() token: " + token.value() + ".");
		Operator op = new Operator(token.value());
		token = lexer.next();
		//System.err.println("equality, after lexer.next() token: " + token.value() + ".");
		e = new Binary(op, e, relation());
		//System.err.println("equality, after relation() token: " + token.value() + ".");
	}
	//System.out.println("end equality, token: " + token.value() + ".");
        return e;  // student exercise
    }

    private Expression relation (){
        // Relation --> Addition [RelOp Addition] 
// addition relOp
//	System.err.println("begin relation, token: " + token.value() + ".");
	Expression e = addition();
//	System.out.println("relation() - token: " + token.value() + ".");
	while (isRelationalOp()) {
		Operator op = new Operator(match(token.type()));
		Expression term2 = addition();
		e = new Binary(op, e, term2);
	}
//	System.out.println("end relation, token: " + token.value() + ".");
        return e;  // student exercise
    }
  
    private Expression addition () {
        // Addition --> Term { AddOp Term }
	//System.err.println("begin addition, token: " + token.value() + ".");
        Expression e = term();
        //System.out.println("additon1, token: " + token.value() + ".");
        while (isAddOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = term();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression term () {
        // Term --> Factor { MultiplyOp Factor }
	//System.err.println("begin term, token: " + token.value() + ".");
        Expression e = factor();
        while (isMultiplyOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = factor();
            e = new Binary(op, e, term2);
        }
	//System.err.println("end term, token: " + token.value() + ".");
        return e;
    }
  
    private Expression factor() {
        // Factor --> [ UnaryOp ] Primary 
//	System.err.println("begin factor, token: " + token.value() + ".");
        if (isUnaryOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term = primary();
  //          System.err.println("end factor (in unary condition), token: " + token.value() + ".");
	    return new Unary(op, term);
        }
	//System.err.println("end factor, token: " + token.value() + ".");
        return primary();
    }
  
    private Expression primary () {
        // Primary --> Identifier | Literal | ( Expression )
        //             | Type ( Expression )
	//System.err.println("begin primary, token: " + token.value() + ".");
        Expression e = null;
        
        if (isLiteral()) {
        //System.err.println("primary isLiteral() true, token: " + token.value() + ".");
            e = literal();
             //System.err.println("primary isLiteral() after lexer.next(), token: " + token.value() + ".");
        } else if (token.type().equals(TokenType.Identifier)) {
        	String id = match(TokenType.Identifier);
        	//System.err.println("2primary, token: " + token.value() + ".");
			if (token.type().equals(TokenType.LeftParen)) {
				//System.err.println("1primary function part, token: " + token.value() + ".");
				token = lexer.next();
				//System.err.println("2primary function part, token: " + token.value() + ".");
				Expression[ ] eA = new Expression[0], eOld = new Expression[0];
				int i = 0;
				while (!(token.type().equals(TokenType.Semicolon)) && !(isAddOp()) && !(isMultiplyOp()) && !(token.type().equals(TokenType.RightParen))) {
					//System.err.println("3primary function part, token: " + token.value() + ".");
					eA = new Expression[++i];
					System.arraycopy(eOld, 0, eA, 0, eOld.length);
					eA[i - 1] = expression();
					//System.err.println("4primary function part, token: " + token.value() + ".");
					eOld = new Expression[i];
					System.arraycopy(eA, 0, eOld, 0, eA.length);
					token = lexer.next();
					//System.err.println("5primary function part, token: " + token.value() + ".");
				}
				if (token.type().equals(TokenType.RightParen)) token = lexer.next();
				//System.err.println("4primary, token: " + token.value() + ".");
				if (token.type().equals(TokenType.Semicolon)) token = lexer.next();
				e = new CallExpr(new Call(id, new Expressions(eA))); // call part
        	} else
            	e = new Variable(id);
        
        } else if (token.type().equals(TokenType.LeftParen)) {
            token = lexer.next();
            e = expression();
            match(TokenType.RightParen);
	    //System.err.println("primary() 3rd if after expression(), token: " + token.value() + ".");
	    if (token.type().equals(TokenType.Semicolon)) {token = lexer.next();}      
	    //System.out.println("primary() (3rd if) -> token: " + token.value() + ".");
            
        } else if (isType( )) {
            Operator op = new Operator(match(token.type()));
            match(TokenType.LeftParen);
            Expression term = expression();
            match(TokenType.RightParen);
            e = new Unary(op, term);
        } else error("primary() -> Identifier | Literal | ( | Type");
	//System.err.println("end primary, token: " + token.value() + ".");
        return e;
    }

    private Value literal( ) {
// Value = IntValue | BoolValue |
//         CharValue | FloatValue
//	System.out.println("begin literal, token: " + token.value() + ".");
        Value v = null;
	if (token.type().equals(TokenType.IntLiteral)) {v = v.mkValue(Type.INT, token.value()); match(TokenType.IntLiteral);}
	else if (token.type().equals(TokenType.CharLiteral)) {v = v.mkValue(Type.CHAR, token.value()); match(TokenType.CharLiteral);}
    else if (token.type().equals(TokenType.FloatLiteral)) {v = v.mkValue(Type.FLOAT, token.value()); match(TokenType.FloatLiteral);}
    else if (token.type().equals(TokenType.True) || token.type().equals(TokenType.False)) {v = v.mkValue(Type.BOOL, token.value()); token = lexer.next();}

//	System.err.println("end literal, token: " + token.value() + ".");
	return v;
    }

    private Boolean isStatement() {
	return token.type().equals(TokenType.Semicolon) || token.type().equals(TokenType.LeftBrace)
	|| token.type().equals(TokenType.Identifier) || token.type().equals(TokenType.If) 
	|| token.type().equals(TokenType.While) || token.type().equals(TokenType.Return);
    }

    private boolean isAddOp( ) {
        return token.type().equals(TokenType.Plus) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isMultiplyOp( ) {
        return token.type().equals(TokenType.Multiply) ||
               token.type().equals(TokenType.Divide);
    }
    
    private boolean isUnaryOp( ) {
        return token.type().equals(TokenType.Not) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isEqualityOp( ) {
        return token.type().equals(TokenType.Equals) ||
            token.type().equals(TokenType.NotEqual);
    }
    
    private boolean isRelationalOp( ) {
        return token.type().equals(TokenType.Less) ||
               token.type().equals(TokenType.LessEqual) || 
               token.type().equals(TokenType.Greater) ||
               token.type().equals(TokenType.GreaterEqual);
    }
    
    private boolean isType( ) {
        return token.type().equals(TokenType.Int)
            || token.type().equals(TokenType.Bool) 
            || token.type().equals(TokenType.Float)
            || token.type().equals(TokenType.Char)
            || token.type().equals(TokenType.Void);
    }
    
    private boolean isLiteral( ) {
        return token.type().equals(TokenType.IntLiteral) ||
            isBooleanLiteral() ||
            token.type().equals(TokenType.FloatLiteral) ||
            token.type().equals(TokenType.CharLiteral);
    }
    
    private boolean isBooleanLiteral( ) {
        return token.type().equals(TokenType.True) ||
            token.type().equals(TokenType.False);
    }
    
    public static void main(String args[]) {
        Parser parser  = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
	System.out.println("Begin parsing ... " + args[0]);
        prog.display();           // display abstract syntax tree
    } //main

} // Parser


/*
COPYPASTA 

    private Function function() {
        Declaration pOld;
        Function f;
        Type t = type();
        token = lexer.next();
        String id = token.value();
        token = lexer.next();
        match(TokenType.LeftParen);
        Declaration[] params = new Declaration[0];
        int i = 0;
        while (isType()) {
            params = new Declaration[++i];
            Type pT = type();
            token = lexer.next();
            params[i - 1] = declaration(pT);
            System.arraycopy(pOld, 0, params, 0, pOld.length);
            pOld = new Declaration[i];
            System.arraycopy(params, 0, pOld, 0, params.length);
            if (token.type().equals(TokenType.Comma)) {match(TokenType.Comma)}
        }
        match(TokenType.RightParen);
        match(TokenType.LeftBrace);
        Declarations locals = declarations();
        Block body = statements();
        match(TokenType.RightBrace);
        return new Function(t, id, params, locals, body);
    }


*/


*/


