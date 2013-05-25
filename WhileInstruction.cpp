#include "WhileInstruction.h"
#include "Interpreter.h"

WhileInstruction::WhileInstruction(void)
{
}

WhileInstruction::WhileInstruction(ExpressionInstruction* _expr, vector<Instruction*> _instructions)
{
	instructions = _instructions;
	expr = _expr;
}
WhileInstruction::~WhileInstruction(void)
{
	delete expr;

	for(size_t i=0; i<instructions.size(); i++)
	{
		delete instructions.at(i);
	}
}

bool WhileInstruction::execute()
{
	if(interpr->isTrace()) cout<<"----------While"<<endl;

	expr->setInterpreter(this->interpr);

	for(;;)																//loop
	{
		//if(expr->getResult()) delete expr->getResult();
		if(expr->execute())												//calc expression
		{
			Value* val =expr->getResult();								//get result
			if(val->isBool())
			{
				interpr->increaseStackLevel();
				if(val->toBool())										//if true
				{
				
					for(size_t i=0; i<instructions.size(); i++)
					{
						instructions.at(i)->setInterpreter(interpr);
						if(!instructions.at(i)->execute())
							return false;
					}
				
				}
				else													//if false
				{
					interpr->decreaseStackLevel();
					break;												
				}
				interpr->decreaseStackLevel();
			}
			else
			{
				cout<<"Line "<<line<<": Expected bool expression"<<endl;
				return false;
			}
		}
		else
		{
			return false;												//expression error
		}
	}
	return true;
}