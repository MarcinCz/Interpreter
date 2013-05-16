#include "SyntaxAnalyzer.h"
#pragma once

enum VarType{
	FractType,
	BoolType,
	UnknownType
};

class VarValue{
	
};
class Variable
{
public:
	Variable(void);
	Variable(string name);
	~Variable(void);

	VarType getType();
	void setType();
	string getName();
	
};

