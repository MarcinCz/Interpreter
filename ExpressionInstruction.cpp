#include "ExpressionInstruction.h"


ExpressionInstruction::ExpressionInstruction(void)
{
}

ExpressionInstruction::ExpressionInstruction(ExpressionTreeNode* _root)
{
	root = _root;
}

ExpressionInstruction::~ExpressionInstruction(void)
{
}

bool ExpressionInstruction::execute()
{
	cout << "expression" <<endl;
	return true;
}

ExpressionTreeNode* ExpressionInstruction::getRoot()
{
	return root;
}