#pragma once

#include "SyntaxAnalyzer.h"
#include "AssigmentInstruction.h"
#include "DeclarationInstruction.h"
#include "ExpressionInstruction.h"
#include "FunDeclarationInstruction.h"
#include "FunInstruction.h"
#include "IfInstruction.h"
#include "PrintInstruction.h"
#include "WhileInstruction.h"


class Interpreter
{
public:
	Interpreter(void);
	Interpreter(vector<Instruction* > instructionList);
	~Interpreter(void);

	//bool isVariableDeclared(string varName);
	Variable* getVariable(string varName);				//null if not declared
	bool addVariable(string varName);

	Function* getFunction(string name, int parameters); //null if not declared
	bool addFunction(string name, int parameters);

	void increaseStackLevel();
	void decreaseStackLevel();
	void setInstructionList(vector<Instruction* > instructionList);
private:
	int stackLevel;
	vector<vector<Variable* > > variableStack;
	vector<Function* > functionList;
	vector<Instruction* > instructionList;
};

