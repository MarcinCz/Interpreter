#pragma once
#include "Instruction.h"

class FunInstruction :
	public Instruction
{
public:
	FunInstruction(void);
	~FunInstruction(void);

	bool execute();
};

