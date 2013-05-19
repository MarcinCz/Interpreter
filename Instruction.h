#pragma once

#include <iostream>
#include <vector>
#include "Variable.h"
//#include "Interpreter.h"

using namespace std;


class Interpreter;

enum InstructionType
{
	AssigmentInst,
	DeclarationInst,
	ExpressionInst,
	FunDeclarationInstr,
	FunInstr,
	IfInstr,
	PrintInstr,
	WhileInstr,
};



class Instruction
{
public: 
	/*Instruction(){}
	Instruction(InstructionType _type)
	{
		type = _type;
	}*/
	virtual ~Instruction(){}
		
	virtual bool execute()=0;
	virtual InstructionType getType() {return type;};
	virtual void setLine(int _line) {line =_line;};
	virtual void setType(InstructionType _type) { type= _type;};
	virtual void setInterpreter(Interpreter* _interpr) {interpr = _interpr;};

protected:
	int line;
	InstructionType type;
	Interpreter* interpr;
};
