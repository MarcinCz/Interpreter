#pragma once

#include "LexicalAnalyzer.h"
#include "Fraction.h"
#include "Variable.h"
#include <vector>

class Instruction
{
public: 
	virtual ~Instruction(){}
		
	virtual bool execute()=0;
};

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(void);
	~SyntaxAnalyzer(void);
private:
	//vector<vector<Variable*>> VariableStack;
};

