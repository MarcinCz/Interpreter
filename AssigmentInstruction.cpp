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
	if(interpr->isTrace()) cout<<"----------Assigment"<<endl;
	Variable* var = interpr->getVariable(varName);						//get variable
	if(var != NULL)
	{
		expr->setInterpreter(this->interpr);
		//if(expr->getResult()) delete expr->getResult();
		if(expr->execute())												//calc expression
		{
			Value* val =new Value(expr->getResult());
			if(!var->getValue()->isUnknown() && (var->getValue()->getType() != val->getType()))
			{
				if(var->getValue()->isFraction())
					cout<<"Line "<<line<<": Type mismatch in assigment. Expected fraction."<<endl;
				else
					cout<<"Line "<<line<<": Type mismatch in assigment. Expected bool."<<endl;
				return false;
			}
			//delete expr->getResult();
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
		cout<<"Line "<<line<<": Undeclared variable '"<<varName<<"' used in assigment"<<endl;
		return false;
	}

}