#include "DeclarationInstruction.h"
#include "Interpreter.h"

DeclarationInstruction::DeclarationInstruction(void)
{
}

DeclarationInstruction::DeclarationInstruction(string _varName)
{
	varName = _varName;
}
DeclarationInstruction::~DeclarationInstruction(void)
{
}

bool DeclarationInstruction::execute()
{
	//creates unknown variable and pushes it on stack
	//Variable var(varName);
	if(interpr->isTrace()) cout<<"----------Declaration" <<endl;


	if(!interpr->addVariable(varName))	
	{
		cout<<"Line "<<line<<": Variable '"<<varName<<"' already declared on that level."<<endl;
		return false;
	}
	return true;
}
