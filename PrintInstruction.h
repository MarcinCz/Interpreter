#pragma once
#include "Instruction.h"
class PrintInstruction :
	public Instruction
{
public:
	PrintInstruction(void);
	PrintInstruction(string toPrint, bool isText);
	~PrintInstruction(void);

	bool execute();

private:
	string toPrint;
	bool isText;

};

