#pragma once
#include "Instruction.h"
#include "ExpressionInstruction.h"

class IfInstruction :
	public Instruction
{
public:
	IfInstruction(void);
	IfInstruction(ExpressionInstruction*, vector<Instruction*>, vector<Instruction*>);
	~IfInstruction(void);

	bool execute();

private:
	ExpressionInstruction* expr;
	vector<Instruction*> ifInstr;
	vector<Instruction*> elseInstr;
};

