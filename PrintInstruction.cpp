#include "PrintInstruction.h"
#include "ExpressionInstruction.h"


PrintInstruction::PrintInstruction(void)
{
}

PrintInstruction::PrintInstruction(string _toPrint)
{
	toPrint =_toPrint;
	isText = true;
}

PrintInstruction::PrintInstruction(ExpressionInstruction* _expr)
{
	expr =_expr;
	isText = false;
}

PrintInstruction::~PrintInstruction(void)
{
	if(!isText)
		delete expr;
}

bool PrintInstruction::execute()
{
		cout<<"----------Print"<<endl;
		if(isText)
		{
			cout << toPrint <<endl;
			return true;
		}
		else
		{
			expr->setInterpreter(this->interpr);
			if(expr->execute())												//calc expression
			{
				cout << expr->getResult()->toString() <<endl;
				//delete expr->getResult();
				return true;
			}
			else
			{
				return false;
			}
		}
}