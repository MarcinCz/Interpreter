#pragma once
#include "Instruction.h"
class IfInstruction :
	public Instruction
{
public:
	IfInstruction(void);
	~IfInstruction(void);

	bool execute();
};

