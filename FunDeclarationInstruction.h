#pragma once

#include "Instruction.h"

class Function
{
public:
	Function() {}
	Function(string _name, int _parameters)
	{
		name = _name;
		parameters = _parameters;
	}
	~Function();

	string getName() { return name; }
	int getParameters() { return parameters; }

private:
	string name;
	int parameters;
};


class FunDeclarationInstruction :
	public Instruction
{
public:
	FunDeclarationInstruction(void);
	~FunDeclarationInstruction(void);

	bool execute();
};

