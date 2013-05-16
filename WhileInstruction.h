#pragma once
#include "syntaxanalyzer.h"
class WhileInstruction :
	public Instruction
{
public:
	WhileInstruction(void);
	~WhileInstruction(void);

	bool execute();
};

