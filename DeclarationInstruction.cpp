#include "DeclarationInstruction.h"


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
	cout<<"Declaration" <<endl;
	return true;
}
