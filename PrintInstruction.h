#pragma once
#include "Instruction.h"

class ExpressionInstruction;

class PrintInstruction :
	public Instruction
{
public:
	PrintInstruction(void);
	PrintInstruction(string toPrint);
	PrintInstruction(ExpressionInstruction* expr);
	~PrintInstruction(void);

	bool execute();

private:
	string toPrint;
	bool isText;
	ExpressionInstruction* expr;

};

