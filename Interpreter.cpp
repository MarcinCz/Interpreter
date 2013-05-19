#include "Interpreter.h"


Interpreter::Interpreter(void)
{
	stackLevel = 0;
	variableStack.push_back(vector<Variable *>());
}

Interpreter::Interpreter(vector<Instruction* > _instructionList)
{
	stackLevel = 0;
	variableStack.push_back(vector<Variable *>());
	instructionList = _instructionList;
}
Interpreter::~Interpreter(void)
{
}

Variable* Interpreter::getVariable(string _varName)
{
	for(int i = stackLevel; i>=0; i--)				//loop on every stack level from the highest
	{
		for(size_t j = 0; j < variableStack.at(i).size(); j++)	//checks one level
		{			
			if(variableStack.at(i).at(j)->getName() == _varName)
				return variableStack.at(i).at(j);
		}
	}
	return NULL;
}

bool Interpreter::addVariable(string _varName)
{
	Variable *var = getVariable(_varName);
	if(var != NULL)
	{
		if(var->getLevel() == stackLevel)
		{
			//cout<<"Variable "<<_varName<<" already declared on that level."<<endl;
			return false;
		}
	}

	//if may be added
	var = new Variable(_varName);
	var->setLevel(stackLevel);

	variableStack.at(stackLevel).push_back(var);
	return true;
}

Function* Interpreter::getFunction(string _name, int _parameters)
{
	for(size_t i = 0; i < functionList.size(); i++)
	{
		if(functionList.at(i)->getName() == _name && functionList.at(i)->getParameters() == _parameters)
		{
			return functionList.at(i);
		}
	}
	return NULL;
}

bool Interpreter::addFunction(string _name, int _parameters)
{
	if(getFunction(_name, _parameters) != NULL)
	{
		//cout<<"Function with that name and parameters number already declared"<<endl;
		return false;
	}

	functionList.push_back(new Function(_name, _parameters));
	return true;
}

bool Interpreter::executeInstructions()
{
	for(size_t i=0; i<instructionList.size(); i++)
	{
		instructionList.at(i)->setInterpreter(this);
		if(!instructionList.at(i)->execute())
		{
			cout << "Interpretation ended with error"<<endl;
			return false;
		}
	}

	cout << "Interpretation ended without errors"<<endl;
	return true;
}
void Interpreter::increaseStackLevel()
{
	variableStack.push_back(vector<Variable *>());
	stackLevel++;
}

void Interpreter::decreaseStackLevel()
{
	variableStack.pop_back();
	stackLevel--;
}

void Interpreter::setInstructionList(vector<Instruction* > _instructionList)
{
	instructionList = _instructionList;
}

