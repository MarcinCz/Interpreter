#include "FunInstruction.h"
#include "Interpreter.h"

FunInstruction::FunInstruction(void)
{
}

FunInstruction::FunInstruction(string _name, vector<string> _params)
{
	name = _name;
	params = _params;
}
FunInstruction::~FunInstruction(void)
{

}

Value* FunInstruction::getResult()
{
	return result;
}
bool FunInstruction::execute()
{
	cout<<"----------FunCall"<<endl;

	Function *fun = interpr->getFunction(name,params.size());	//check if function is declared
	if(fun != NULL)
	{
		interpr->increaseStackLevel();
		interpr->setOnlyHighestStack(true);
		for(size_t i=0; i<params.size(); i++)						//try to get variables from parameters
		{
			Variable* var = interpr->getVariableFromLowerStack(params.at(i));
			if(var != NULL)											//check if variable declared
			{
				if( var->getValue()->getType() != UnknownType )		//check if variable definied
				{
					interpr->addVariable(new Variable(fun->getParameters().at(i),new Value(var->getValue())));	//add new variable to stack

					for(size_t j=0; j < fun->getInstructions().size(); j++)			//execute instructions
					{
						fun->getInstructions().at(j)->setInterpreter(interpr);
						if(!fun->getInstructions().at(j)->execute())				//if execution failed return
						{	
							interpr->setOnlyHighestStack(false);
							return false;
						}
					}

					fun->getReturnExpr()->setInterpreter(interpr);
					if(fun->getReturnExpr()->execute())								//calc return value
						result=fun->getReturnExpr()->getResult();
					else
					{
						interpr->setOnlyHighestStack(false);
						return false;
					}
				}
				else
				{
					interpr->setOnlyHighestStack(false);
					cout<<"Line "<<line<<": Undefined variable '"<<params.at(i)<<"' used in function call"<<endl;
					return false;
				}
			}
			else
			{
				interpr->setOnlyHighestStack(false);
				cout<<"Line "<<line<<": Undeclared variable '"<<params.at(i)<<"' used in function call"<<endl;
				return false;
			}

		}

		interpr->setOnlyHighestStack(false);
		interpr->decreaseStackLevel();
		return true;
	}
	else
	{
		cout<<"Line "<<line<<": Undeclared function '"<<name<<"' used in expression"<<endl;
		return false;
	}

}