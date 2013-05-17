#pragma once

/*********
	Program 	= ProgramLine, {ProgramLine};
	ProgramLine	= Statement | Instruction ;
	Statement	= WhileStment | IfStment | FunStment;
	WhileStment	= 'while', '(', Expression, ')', Block;
	IfStment	= 'if', '(', Expression, ')', Block, ['else', Block];
	FunStment	= 'function', ident, Params, FunBlock;

	Assigment	=  ident, '=', Expression,';';
	Expression	= SimpleExp | SimpleExp, RelOp, SimpleExp;
	SimpleExp	= AndExpr | AndExpr AndOp AndExpr;
	AndExpr		= OrExpr | OrExpr OrOp OrExpr;
	OrExpr		= '!',OrExpr | ident | fractconst | boolconst | FunCall | '(',Expression,')';
	RelOp 		= '<=' | '>=' | '>' | '<' | '==' | '!=';
	AndOp 		= '*' | '/' | 'and';
	OrOp 		= '+' | '-' | 'or';

	Params		= '(', ')' | '(', ident, {',', ident}, ')';
	Block		= '{', {Instruction | WhileStment | IfStment}, '}';
	FunBlock	= '{', {Instruction | WhileStment | IfStment}, 'return', Expression, ';}';
	Instruction	= Declaration | Assigment | FunCall,';' | PrintCall |;
	Declaration	= ident, ';';
	FunCall		= '^', ident, Params;
	PrintCall	= 'print', '(', [ident | text], ')';
***********/

#include "LexicalAnalyzer.h"
#include "Fraction.h"
#include "Variable.h"

#include <vector>

class Instruction
{
public: 
	//Instruction(){}
	virtual ~Instruction(){}
		
	virtual bool execute()=0;
};

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(void);
	SyntaxAnalyzer(LexicalAnalyzer* lexAnalyzer);
	~SyntaxAnalyzer(void);

	bool Program();
private:

	bool ProgramLine();
	bool Statement();
	bool WhileStatement();
	bool IfStatement();
	bool FunStatement();

	//bool Assigment();
	bool Expression();
	bool SimpleExpression();
	bool AndExpression();
	bool OrExpression();
	bool RelOp();
	bool AndOp();
	bool OrOp();

	bool Params();
	bool Block();
	bool FunBlock();
	bool InstructionS();
	//bool Declaration();
	bool FunCall();
	bool PrintCall();
	bool FractConst();

	void advance();
	void errorInfo(string info);
	Symbol currentSymbol;
	vector<Instruction*> InstructionList;
	LexicalAnalyzer* lexAnalyzer;
};

