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

enum InstructionType
{
	AssigmentInst,
	DeclarationInst,
	ExpressionInst,
	FunDeclarationInstr,
	FunInstr,
	IfInstr,
	PrintInstr,
	WhileInstr,
};

class Instruction
{
public: 
	/*Instruction(){}
	Instruction(InstructionType _type)
	{
		type = _type;
	}*/
	virtual ~Instruction(){}
		
	virtual bool execute()=0;
	virtual InstructionType getType() {return type;};
	virtual void setType(InstructionType _type) { type= _type;};

protected:
	InstructionType type;
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
	SymbolType RelOp();
	SymbolType AndOp();
	SymbolType OrOp();

	/*ExpressionTreeNode* Expression();
	ExpressionTreeNode* SimpleExpression();
	ExpressionTreeNode* AndExpression();
	ExpressionTreeNode* OrExpression();
	SymbolType RelOp();
	SymbolType AndOp();
	SymbolType OrOp();*/

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

