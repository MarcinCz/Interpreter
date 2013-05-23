#include "AssigmentInstruction.h"
#include "Interpreter.h"

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
	delete expr;
}

bool AssigmentInstruction::execute()
{
	cout<<"----------Assigment"<<endl;
	Variable* var = interpr->getVariable(varName);						//get variable
	if(var != NULL)
	{
		expr->setInterpreter(this->interpr);
		if(expr->execute())												//calc expression
		{
			Value* val =new Value(expr->getResult());
			var->setValue(val);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout<<"Line "<<line<<": Undeclared variable '"<<varName<<"' used in expression"<<endl;
		return false;
	}

}