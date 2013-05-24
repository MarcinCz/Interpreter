#include "IfInstruction.h"
#include "Interpreter.h"

IfInstruction::IfInstruction(void)
{
}

IfInstruction::IfInstruction(ExpressionInstruction* _expr, vector<Instruction*> _ifInstr, vector<Instruction*> _elseInstr)
{
	expr = _expr;
	ifInstr = _ifInstr;
	elseInstr = _elseInstr;
}

IfInstruction::~IfInstruction(void)
{
	delete expr;

	for(size_t i=0; i<ifInstr.size(); i++)
	{
		delete ifInstr.at(i);
	}
	
	for(size_t i=0; i<elseInstr.size(); i++)
	{
		delete elseInstr.at(i);
	}
}

bool IfInstruction::execute()
{
	cout<<"----------If"<<endl;

	expr->setInterpreter(this->interpr);
	if(expr->execute())												//calc expression
	{
		Value* val =expr->getResult();								//get result
		if(val->isBool())
		{
			interpr->increaseStackLevel();
			if(val->toBool())										//if true
			{
				
				for(size_t i=0; i<ifInstr.size(); i++)
				{
					ifInstr.at(i)->setInterpreter(interpr);
					if(!ifInstr.at(i)->execute())
						return false;
				}
				
			}
			else													//if false
			{

				for(size_t i=0; i<elseInstr.size(); i++)
				{
					elseInstr.at(i)->setInterpreter(interpr);
					if(!elseInstr.at(i)->execute())
						return false;
				}
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

	return true;
}