#pragma once

#include "Instruction.h"
#include "Variable.h"
#include <vector>


enum ExpressionTreeNodeType
{
	variableNodeType,
	valueNodeType,
	funNodeType,
	operatorNodeType,
	unknowndNodeType,
};

/**************ExpressionTreeNode************************/

class ExpressionTreeNode
{
public:
	ExpressionTreeNode() { type = unknowndNodeType; }
	ExpressionTreeNode(Variable* _nodeVariable)
	{
		type = variableNodeType;
		nodeVariable = _nodeVariable;
	}
	ExpressionTreeNode(SymbolType _nodeOperator)
	{
		type = operatorNodeType;
		nodeOperator = _nodeOperator;
	}
	ExpressionTreeNode(Value* _nodeValue)
	{
		type = valueNodeType;
		nodeValue = _nodeValue;
	}
	ExpressionTreeNode(Instruction* _nodeFunInstruction)
	{
		type = funNodeType;
		nodeFunInstruction = _nodeFunInstruction;
	}
	~ExpressionTreeNode(){}

	int getChildrenCount(){ return children.size(); }
	Variable* getVariable() { return nodeVariable; }
	SymbolType getOperator() { return nodeOperator; }
	Value* getValue() { return nodeValue; }
	Instruction* getFunInstruction() { return nodeFunInstruction; }

	void setVariable(Variable* _nodeVariable)
	{
		type = variableNodeType;
		nodeVariable = _nodeVariable;
	}
	void setValue(Value* _nodeValue)
	{
		type = valueNodeType;
		nodeValue = _nodeValue;
	}
	void setOperator(SymbolType _nodeOperator)
	{
		type = operatorNodeType;
		nodeOperator = _nodeOperator;
	}
	
	ExpressionTreeNode* getParent() { return parent; }
	ExpressionTreeNode* getChildAt(int pos) {return children.at(pos); }
	ExpressionTreeNodeType getType() { return type; }

	void setParent(ExpressionTreeNode* _parent) { parent = _parent; }
	void addChild(ExpressionTreeNode* _child) { children.push_back(_child); }

private:
	ExpressionTreeNode* parent;
	vector<ExpressionTreeNode*> children;
	ExpressionTreeNodeType type;

	//only one of those is set, depending on node type
	Variable* nodeVariable;
	Value* nodeValue;
	SymbolType nodeOperator;
	Instruction* nodeFunInstruction;
};


/*********************ExpressionInstruction*********************************/
class ExpressionInstruction :
	public Instruction
{
public:
	ExpressionInstruction(void);
	ExpressionInstruction(ExpressionTreeNode *root);
	~ExpressionInstruction(void);

	bool execute();
	ExpressionTreeNode* getRoot();

private:
	ExpressionTreeNode* root;
};

