#include "AssigmentInstruction.h"


AssigmentInstruction::AssigmentInstruction(void)
{
}

AssigmentInstruction::AssigmentInstruction(string _varName, ExpressionInstruction* _expr)
{
	expr = _expr;
	varName = _varName;
}
AssigmentInstruction::~AssigmentInstruction(void)
{
}

bool AssigmentInstruction::execute()
{
	cout<<"Assigment"<<endl;
	return true;
}