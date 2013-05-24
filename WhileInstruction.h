#pragma once
#include "Instruction.h"
#include "ExpressionInstruction.h"

class WhileInstruction :
	public Instruction
{
public:
	WhileInstruction(void);
	WhileInstruction(ExpressionInstruction*, vector<Instruction*>);
	~WhileInstruction(void);

	bool execute();

private:
	ExpressionInstruction* expr;
	vector<Instruction*> instructions;
};

