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
	for(size_t i=0; i<instructionList.size(); i++)
	{
		delete instructionList.at(i);
	}

	for(size_t i=0; i<functionList.size(); i++)
	{
		delete functionList.at(i);	
	}

	for(size_t i = 0; i < variableStack.at(0).size(); i++)	//checks one level
	{			
		delete variableStack.at(0).at(i);
	}

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

Variable* Interpreter::getVariableFromLowerStack(string _varName)
{
	for(int i = stackLevel-1; i>=0; i--)				//loop on every stack level from the highest
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

bool Interpreter::addVariable(Variable* var)
{
	Variable *varFromStack = getVariable(var->getName());
	if(varFromStack != NULL)
	{
		if(varFromStack->getLevel() == stackLevel)
		{
			//cout<<"Variable "<<_varName<<" already declared on that level."<<endl;
			return false;
		}
	}

	//if may be added
	var->setLevel(stackLevel);

	variableStack.at(stackLevel).push_back(var);
	return true;
}

Function* Interpreter::getFunction(string _name, int _parameters)
{
	for(size_t i = 0; i < functionList.size(); i++)
	{
		if(functionList.at(i)->getName() == _name && functionList.at(i)->getParametersCount() == _parameters)
		{
			return functionList.at(i);
		}
	}
	return NULL;
}

bool Interpreter::addFunction(Function* fun)
{
	if(getFunction(fun->getName(), fun->getParametersCount()) != NULL)
	{
		//cout<<"Function with that name and parameters number already declared"<<endl;
		return false;
	}

	functionList.push_back(fun);
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
	for(size_t i = 0; i < variableStack.at(stackLevel).size(); i++)	//checks one level
	{			
		delete variableStack.at(stackLevel).at(i);
	}
	variableStack.pop_back();
	stackLevel--;
}

void Interpreter::setInstructionList(vector<Instruction* > _instructionList)
{
	instructionList = _instructionList;
}

