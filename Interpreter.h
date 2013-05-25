#pragma once

#include "Variable.h"
#include <vector>
#include "AssigmentInstruction.h"
#include "DeclarationInstruction.h"
#include "ExpressionInstruction.h"
#include "FunDeclarationInstruction.h"
#include "FunInstruction.h"
#include "IfInstruction.h"
#include "PrintInstruction.h"
#include "WhileInstruction.h"

//class AssigmentInstruction;
//class DeclarationInstruction;
//class ExpressionInstruction;
//class FunDeclarationInstruction;
//class FunInstruction;
//class IfInstruction;
//class PrintInstruction;
//class WhileInstruction;
//class Function;
//class Instruction;

class Interpreter
{
public:
	Interpreter(void);
	Interpreter(vector<Instruction* > instructionList);
	~Interpreter(void);

	//bool isVariableDeclared(string varName);
	Variable* getVariable(string varName);				//null if not declared
	Variable* getVariableFromLowerStack(string _varName);//null if not declared, used by functionCall
	bool addVariable(string varName);
	bool addVariable(Variable* var);

	Function* getFunction(string name, int parameters); //null if not declared
	bool addFunction(Function* f);

	bool executeInstructions();
	void increaseStackLevel();
	void decreaseStackLevel();
	void setInstructionList(vector<Instruction* > instructionList);
	void setOnlyHighestStack(bool onlyHighestStack);

	void setTrace(bool trace);
	bool isTrace();
private:
	int stackLevel;
	bool onlyHighestStack;		//for functions
	vector<vector<Variable* > > variableStack;
	vector<Function* > functionList;
	vector<Instruction* > instructionList;
	bool trace;
};

