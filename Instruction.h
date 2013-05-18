#pragma once

#include <iostream>
using namespace std;

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
	virtual void setType(InstructionType _type) { type= _type;};

protected:
	InstructionType type;
};
