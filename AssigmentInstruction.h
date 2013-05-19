#pragma once

#include "Instruction.h"

class ExpressionInstruction;

class AssigmentInstruction:
	public Instruction
{
public:
	AssigmentInstruction(void);
	AssigmentInstruction(string varName, ExpressionInstruction* expr);
	~AssigmentInstruction(void);

	bool execute();

private:
	string varName;
	ExpressionInstruction* expr;
};

