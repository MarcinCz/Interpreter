#include "ExpressionInstruction.h"
#include "Interpreter.h"

ExpressionInstruction::ExpressionInstruction(void)
{
}

ExpressionInstruction::ExpressionInstruction(ExpressionTreeNode* _root)
{
	root = _root;
}

ExpressionInstruction::~ExpressionInstruction(void)
{
	delete result;
}

bool ExpressionInstruction::execute()
{
	cout << "expression" <<endl;
	return true;
}

Value* ExpressionInstruction::calcTreeValue(ExpressionTreeNode* root)
{
	if(root->getType() == variableNodeType)					//variable node
	{
		string varName = root->getVariable()->getName();
		Variable* var = interpr->getVariable(varName);
		if(var == NULL)										//variable not found
		{
			cout<<"Undeclared variable "<<varName<<" used in expression"<<endl;
			return NULL;
		}
		if(var->getValue().getType() == UnknownType)		//variable not defined
		{
			cout<<"Undefined variable "<<varName<<" used in expression"<<endl;
			return NULL;
		}
		
		return &(var->getValue());
		
	}

	if(root->getType() == valueNodeType)					//value node
	{
		return root->getValue();
	}

	if(root->getType() == funNodeType)
	{
		return NULL;										//TODO:fun node
	}

	if(root->getType() == operatorNodeType)					//! node
	{
		Value* val = calcTreeValue(root->getChildAt(0));
		if(val->getType() != BoolType)						//not bool
		{
			cout<< "Negating not-bool expression"<<endl;
			return NULL;
		}

		if(val->getBool())									//true->false
		{
			val->setValue(false);
			return val;
		}
		else												//false->true
		{
			val->setValue(true);
			return val;
		}
	}


	if(root->getType() == unknowndNodeType)					//unknown type
	{
		if(root->getChildrenCount() == 0)					//0 children
			return NULL;
		
		


		//Value* valLeft = 

	}

	return NULL;

}


ExpressionTreeNode* ExpressionInstruction::getRoot()
{
	return root;
}

Value* ExpressionInstruction::getResult()
{
	return result;
}