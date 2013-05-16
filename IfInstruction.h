#pragma once
#include "syntaxanalyzer.h"
class IfInstruction :
	public Instruction
{
public:
	IfInstruction(void);
	~IfInstruction(void);

	bool execute();
};

