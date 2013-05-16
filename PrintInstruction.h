#pragma once
#include "syntaxanalyzer.h"
class PrintInstruction :
	public Instruction
{
public:
	PrintInstruction(void);
	~PrintInstruction(void);

	bool execute();
};

