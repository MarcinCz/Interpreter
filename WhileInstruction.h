#pragma once
#include "Instruction.h"
class WhileInstruction :
	public Instruction
{
public:
	WhileInstruction(void);
	~WhileInstruction(void);

	bool execute();
};

