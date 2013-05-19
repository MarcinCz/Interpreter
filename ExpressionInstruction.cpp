#include "ExpressionInstruction.h"
#include "Interpreter.h"
#include "LexicalAnalyzer.h"

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
	result = calcTreeValue(root);
	if(result)
	{
		cout<<result->toString()<<endl;
		return true;
	}
	else 
		return false;
}

Value* ExpressionInstruction::calcTreeValue(ExpressionTreeNode* root)
{
	if(root->getType() == variableNodeType)					//variable node
	{
		string varName = root->getVariable()->getName();
		Variable* var = interpr->getVariable(varName);
		if(var == NULL)										//variable not found
		{
			cout<<"Line "<<line<<": Undeclared variable '"<<varName<<"' used in expression"<<endl;
			return NULL;
		}
		if(var->getValue().getType() == UnknownType)		//variable not defined
		{
			cout<<"Line "<<line<<": Undefined variable '"<<varName<<"' used in expression"<<endl;
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
		if(root->getChildrenCount() == 0)					//0 children
			return NULL;

		Value* val = calcTreeValue(root->getChildAt(0));
		//delete root->getChildAt(0);

		if(val == NULL)
			return NULL;
		if(val->getType() != BoolType)						//not bool
		{
			cout<< "Line "<<line<<": Negating non-bool expression"<<endl;
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
		//Value *valReturned = new Value();
		if(root->getChildrenCount() == 0)					//0 children
			return NULL;
		
		Value* valLeft = calcTreeValue(root->getChildAt(0));	//left value
		//delete root->getChildAt(0);

		if(valLeft == NULL)
		{
			//delete root->getChildAt(0);
			return NULL;
		}

		//valReturned->setType(valLeft->getType());				//setting val type

		for(int i=1; i<root->getChildrenCount(); i+=2)
		{
			SymbolType s = root->getChildAt(i)->getOperator();		//operator
			Value *valRight = calcTreeValue(root->getChildAt(i+1));	//right value

			if(s >= PlusSym && s <= LessEqSym)						//if fract operator
			{
				//if(s >= PlusSym && s<=DivideSym)					//setting return type
				//	valReturned->setType(FractType);
				//else
				//	valReturned->setType(BoolType);

				if(valLeft->getType() != FractType || valRight->getType() != FractType)			//type mismatch
				{
					cout << "Line "<<line<<": Type mismatch in expression (expected fraction, got bool)"<<endl;
					return NULL;
				}

				switch(s)
				{
					case PlusSym:
					{
						Fraction* oldVal=valLeft->getFraction();
						valLeft->setValue(new Fraction(*(valLeft->getFraction()) + *(valRight->getFraction()))); 
						delete oldVal;
						break;
					}
					case MinusSym:
					{
						Fraction* oldVal=valLeft->getFraction();
						valLeft->setValue(new Fraction(*(valLeft->getFraction()) - *(valRight->getFraction())));
						delete oldVal;
						break;
					}
					case MultiSym:
					{
						Fraction* oldVal=valLeft->getFraction();
						valLeft->setValue(new Fraction(*(valLeft->getFraction()) * *(valRight->getFraction())));
						delete oldVal;
						break;
					}
					case DivideSym:
					{
						Fraction* oldVal=valLeft->getFraction();
						valLeft->setValue(new Fraction(*(valLeft->getFraction()) / *(valRight->getFraction())));
						delete oldVal;
						break;
					}
					case GreaterSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) > *(valRight->getFraction()));
						break;
					}
					case LessSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) < *(valRight->getFraction()));
						break;
					}
					case EqualSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) == *(valRight->getFraction()));
						break;
					}
					case NotEqualSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) != *(valRight->getFraction()));
						break;
					}
					case GreaterEqSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) >= *(valRight->getFraction()));
						break;
					}
					case LessEqSym:
					{
						valLeft->setValue(*(valLeft->getFraction()) <= *(valRight->getFraction()));
						break;
					}
				}//switch
			}//if fract operator
			
		}//for
		//valReturned->setValue(valLeft->getValue());
		return valLeft;
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