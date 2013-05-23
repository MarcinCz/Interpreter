#pragma once

#include "Instruction.h"

class ExpressionInstruction;

class Function
{
public:
	Function() {}
	Function(string _name, vector<string> _parameters, vector<Instruction* > _instructions, ExpressionInstruction* _expr)
	{
		name = _name;
		parameters = _parameters;
		instructions = _instructions;
		returnExpr = _expr;
	}
	~Function()
	{
		//delete returnExpr;
		for(size_t i = 0; i<instructions.size(); i++)
			delete instructions.at(i);
	}

	string getName() { return name; }
	int getParametersCount() { return parameters.size(); }
	vector<string> getParameters() { return parameters; }
	vector<Instruction* > getInstructions() { return instructions; }
	ExpressionInstruction* getReturnExpr() { return returnExpr; }

private:
	string name;
	vector<string> parameters;
	vector<Instruction* > instructions;
	ExpressionInstruction* returnExpr;
};


class FunDeclarationInstruction :
	public Instruction
{
public:
	FunDeclarationInstruction();
	FunDeclarationInstruction(string _name, vector<string> _parameters, vector<Instruction* > _instructions, ExpressionInstruction* _expr);	
	~FunDeclarationInstruction(void);

	bool execute();

private:
	string name;
	vector<string> parameters;
	vector<Instruction* > instructions;
	ExpressionInstruction* returnExpr;
};

