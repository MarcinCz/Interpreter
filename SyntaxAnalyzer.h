#pragma once

#include "LexicalAnalyzer.h"
#include "Fraction.h"

class Instruction
{
public: 
	virtual ~Instruction();
		
	virtual bool execute();
};

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(void);
	~SyntaxAnalyzer(void);
};

