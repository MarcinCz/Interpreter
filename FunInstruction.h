#pragma once
#include "Instruction.h"

class FunInstruction :
	public Instruction
{
public:
	FunInstruction(void);
	FunInstruction(string name, vector<string> params);
	~FunInstruction(void);

	Value* getResult();
	bool execute();

private:
	string name;
	vector<string> params;
	Value *result;
};

