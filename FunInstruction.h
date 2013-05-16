#pragma once
#include "syntaxanalyzer.h"
class FunInstruction :
	public Instruction
{
public:
	FunInstruction(void);
	~FunInstruction(void);

	bool execute();
};

