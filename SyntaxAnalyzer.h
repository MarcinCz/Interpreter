#include "LexicalAnalyzer.h"

#pragma once

class Instruction
{
public: 
	virtual ~Instruction();
		
	virtual bool execute();
}

class SyntaxAnalyzer
{
public:
	SyntaxAnalyzer(void);
	~SyntaxAnalyzer(void);
};

