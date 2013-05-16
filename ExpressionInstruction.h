#pragma once
#include "syntaxanalyzer.h"

enum ExpressionTreeNodeType
{
	variableNodeType,
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
	~ExpressionTreeNode(){}

	int getChildrenCount(){ return children.size(); }
	Variable* getVariable() {return nodeVariable; }
	SymbolType getOperator() {return nodeOperator; }
	
	
	ExpressionTreeNode* getParent() { return parent; }
	ExpressionTreeNode* getChildAt(int pos) {return children.at(pos); }

	void setParent(ExpressionTreeNode* _parent) { parent = _parent; }
	void addChild(ExpressionTreeNode* _child) { children.push_back(_child); }



private:
	ExpressionTreeNode* parent;
	vector<ExpressionTreeNode*> children;
	ExpressionTreeNodeType type;
	Variable* nodeVariable;
	SymbolType nodeOperator;
};

/*********************ExpressionInstruction*********************************/
class ExpressionInstruction :
	public Instruction
{
public:
	ExpressionInstruction(void);
	~ExpressionInstruction(void);
};

