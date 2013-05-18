#pragma once

#include "Instruction.h"

class DeclarationInstruction :
	public Instruction
{
public:
	DeclarationInstruction(void);
	DeclarationInstruction(string varName);
	~DeclarationInstruction(void);

	bool execute();

private:
	string varName;
};

