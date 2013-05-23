#include "FunDeclarationInstruction.h"
#include "Interpreter.h"

FunDeclarationInstruction::FunDeclarationInstruction(void)
{
}

FunDeclarationInstruction::FunDeclarationInstruction(string _name, vector<string> _parameters, vector<Instruction* > _instructions, ExpressionInstruction* _expr)
{
	name = _name;
	parameters = _parameters;
	instructions = _instructions;
	returnExpr = _expr;
}

FunDeclarationInstruction::~FunDeclarationInstruction(void)
{

}

bool FunDeclarationInstruction::execute()
{
	cout<<"----------Fundec"<<endl;

	if(interpr->addFunction(new Function(name, parameters, instructions, returnExpr)))
	{
		return true;
	}
	return true;
}