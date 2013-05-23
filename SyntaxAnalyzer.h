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
	SimpleExp	= OrExpr { OrOp OrExpr };
	OrExpr		= AndExpr { AndOp AndExpr };
	AndExpr		= '!',AndExpr | ident | fractconst | boolconst | FunCall | '(',Expression,')';
	RelOp 		= '<=' | '>=' | '>' | '<' | '==' | '!=';
	OrOp 		= '+' | '-' | 'or';
	AndOp 		= '*' | '/' | 'and';
	

	Params		= '(', ')' | '(', ident, {',', ident}, ')';
	Block		= '{', {Instruction | WhileStment | IfStment}, '}';
	FunBlock	= '{', {Instruction | WhileStment | IfStment}, 'return', Expression, ';}';
	Instruction	= Declaration | Assigment | FunCall,';' | PrintCall |;
	Declaration	= ident, ';';
	FunCall		= '^', ident, Params;
	PrintCall	= 'print', '(', [Expression | text], ')';
***********/

#include "LexicalAnalyzer.h"
#include "Fraction.h"
#include "Variable.h"
#include "ExpressionInstruction.h"
#include <vector>


class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(void);
	SyntaxAnalyzer(LexicalAnalyzer* lexAnalyzer);
	~SyntaxAnalyzer(void);

	vector<Instruction*> getInstructionList();
	bool Program();
private:

	bool ProgramLine();
	bool Statement();
	bool WhileStatement();
	bool IfStatement();
	bool FunStatement();

	//bool Assigment();
	ExpressionTreeNode* Expression();
	ExpressionTreeNode* SimpleExpression();
	ExpressionTreeNode* AndExpression();
	ExpressionTreeNode* OrExpression();
	SymbolType RelOp();
	SymbolType AndOp();
	SymbolType OrOp();

	bool Params();
	bool Block();
	bool FunBlock();
	Instruction* InstructionS();
	Instruction* FunCall();
	Instruction* PrintCall();
	Fraction* FractConst();

	void advance();
	void errorInfo(string info);
	Symbol currentSymbol;
	vector<Instruction*> InstructionList;
	LexicalAnalyzer* lexAnalyzer;
};

