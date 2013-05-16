#pragma once
#include "SyntaxAnalyzer.h"

class AssigmentInstruction:
	public Instruction
{
public:
	AssigmentInstruction(void);
	~AssigmentInstruction(void);

	bool execute();
};

