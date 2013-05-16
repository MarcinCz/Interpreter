#pragma once
#include "syntaxanalyzer.h"
class FunDeclarationInstruction :
	public Instruction
{
public:
	FunDeclarationInstruction(void);
	~FunDeclarationInstruction(void);

	bool execute();
};

