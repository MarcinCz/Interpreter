#pragma once

#include "Instruction.h"

class AssigmentInstruction:
	public Instruction
{
public:
	AssigmentInstruction(void);
	~AssigmentInstruction(void);

	bool execute();
};

