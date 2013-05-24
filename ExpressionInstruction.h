#pragma once

#include "Instruction.h"
#include "FunInstruction.h"
#include "Variable.h"
#include <vector>


enum ExpressionTreeNodeType
{
	variableNodeType,
	valueNodeType,
	funNodeType,
	operatorNodeType,
	unknowndNodeType,
	errorNodeType,
};

/**************ExpressionTreeNode************************/

class ExpressionInstruction;

class ExpressionTreeNode
{
public:
	//Constructors
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
	ExpressionTreeNode(FunInstruction* _nodeFunInstruction)
	{
		type = funNodeType;
		nodeFunInstruction = _nodeFunInstruction;
	}
	~ExpressionTreeNode(){
		//clearTree(this);
	}

	//Getters
	int						getChildrenCount(){ return children.size(); }
	Variable*				getVariable() { return nodeVariable; }
	SymbolType				getOperator() { return nodeOperator; }
	Value*					getValue() { return nodeValue; }
	FunInstruction*			getFunInstruction() { return nodeFunInstruction; }
	ExpressionTreeNode*		getParent() { return parent; }
	ExpressionTreeNode*		getChildAt(int pos) {return children.at(pos); }
	ExpressionTreeNodeType	getType() { return type; }

	//Setters
	void setType(ExpressionTreeNodeType _type)
	{
		type = _type;
	}
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
	FunInstruction* nodeFunInstruction;
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
	Value* getResult();
	

private:
	void clearTree(ExpressionTreeNode* node);
	Value* calcTreeValue(ExpressionTreeNode* node);
	ExpressionTreeNode* root;
	Value* result;
};

