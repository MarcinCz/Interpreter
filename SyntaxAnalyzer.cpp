#include "SyntaxAnalyzer.h"
#include "AssigmentInstruction.h"
#include "DeclarationInstruction.h"
#include "ExpressionInstruction.h"
#include "FunDeclarationInstruction.h"
#include "FunInstruction.h"
#include "IfInstruction.h"
#include "PrintInstruction.h"
#include "WhileInstruction.h"
#include "Interpreter.h" //TODO: usunac

#include <sstream>

SyntaxAnalyzer::SyntaxAnalyzer(void)
{
}

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer* _lexAnalyzer)
{
	lexAnalyzer = _lexAnalyzer;
}

SyntaxAnalyzer::~SyntaxAnalyzer(void)
{
}

void SyntaxAnalyzer::advance()
{
	currentSymbol = lexAnalyzer->getNextSymbol();
}

void SyntaxAnalyzer::errorInfo(string _info)
{
	cout<< "Expected "<<_info<<" at line:"<<currentSymbol.getPosition().second<<", column:"<<currentSymbol.getPosition().first<<endl;
}

vector<Instruction*> SyntaxAnalyzer::getInstructionList()
{
	return InstructionList;
}
bool SyntaxAnalyzer::Program()
{
	advance();

	while(currentSymbol.getSymbolType() != EOFSym)
	{
		if(!ProgramLine())
		{
			cout << "Syntax analysis completed with errors." << endl;
			return false;
		}
	}

	cout << "Syntax analysis completed without errors." << endl;
	return true;

}

bool SyntaxAnalyzer::ProgramLine()
{
	Instruction* i;
	//i = Statement();
	if(Statement())
		return true;
	else 
	{
		i = InstructionS();
		if(i != NULL)
		{
			InstructionList.push_back(i);
			return true;
		}
	}
	
	errorInfo("statement or instruction");   
	return false;


}

bool SyntaxAnalyzer::Statement()
{
	Instruction* i;
	if(WhileStatement())
	{
		return true;
	}
	if(IfStatement())
	{
		return true;
	}
	i = FunStatement();
	if(i != NULL)
	{
		InstructionList.push_back(i);
		return true;
	}
	else
		return false;
}

bool SyntaxAnalyzer::WhileStatement()
{
	WhileInstruction w;
	if(currentSymbol.getSymbolType() == WhileSym)					//while
	{
		advance();
		if(currentSymbol.getSymbolType() == LBracketSym)			//(
		{
			advance();
			if(Expression())										//expr
			{				
				if(currentSymbol.getSymbolType() == RBracketSym)	//)
				{
					advance();
					if(Block())										//block
					{
						
						w.execute();
						return true;
					}
					else
						return false;
				}
				else
				{
					errorInfo(")");
					return false;
				}
			}
			else return false;
		}
		else 
		{
			errorInfo("'('");
			return false;

		}
	}
	else return false;
}

bool SyntaxAnalyzer::IfStatement()
{
	IfInstruction w;
	if(currentSymbol.getSymbolType() == IfSym)					//if
	{
		advance();
		if(currentSymbol.getSymbolType() == LBracketSym)			//(
		{
			advance();
			if(Expression())										//expr
			{
				if(currentSymbol.getSymbolType() == RBracketSym)	//)
				{
					advance();
					if(Block())										//block
					{
						if(currentSymbol.getSymbolType() == ElseSym)//else
						{
							advance();
							if(Block())								//block
							{
								w.execute();
								return true;
							}
							return false;
						}					
						w.execute();
						return true;
					}
					else return false;
				}
				else
				{
					errorInfo(")");
					return false;
				}
			}
			else return false;
		}
		else 
		{
			errorInfo("'('");
			return false;

		}
	}
	else return false;
}

Instruction* SyntaxAnalyzer::FunStatement()
{

	FunDeclarationInstruction* f;
	pair<bool,vector<string> > paramsReturn;
	pair<ExpressionInstruction*,vector<Instruction*> > funBlockReturn;
	string id;

	if(currentSymbol.getSymbolType() == FunctionSym)				//function
	{
		advance();
		if(currentSymbol.getSymbolType() == IdentSym)				//ident
		{
			id = currentSymbol.getValue();
			advance();
			paramsReturn = Params();
			if(paramsReturn.first)									//params
			{			
				funBlockReturn = FunBlock();
				if(funBlockReturn.first != NULL)					//funblock
				{
					//f.execute();
					f = new FunDeclarationInstruction(id, paramsReturn.second, funBlockReturn.second, funBlockReturn.first);
					f->setLine(lexAnalyzer->getRow());
					return f;				
				}
				else
				{
					return false;
				}
			}
			else return false;
		}
		else 
		{
			errorInfo("function identifier");
			return false;

		}
	}
	else return false;
}

//bool SyntaxAnalyzer::Assigment()  //TODO. zwraca assigmentInstruction
//{
//	AssigmentInstruction w;
//	if(currentSymbol.getSymbolType() == IdentSym)					//id
//	{
//		advance();
//		if(currentSymbol.getSymbolType() == AssigmentSym)			//=
//		{
//			advance();
//			if(Expression())										//expr
//			{
//				if(currentSymbol.getSymbolType() == SemicolonSym)	//;
//				{
//					w.execute();
//					return true;
//				}
//				else
//				{
//					errorInfo("';'");
//					return false;
//				}
//				
//			}
//			else
//				return false;
//		}
//		else
//		{
//			errorInfo("'='");
//			return false;
//		}
//	}
//	else
//		return false;
//}

ExpressionTreeNode* SyntaxAnalyzer::Expression()  //TODO:zwraca
{
	SymbolType s;
	ExpressionTreeNode* node;
	ExpressionTreeNode* returnNode;

	node = SimpleExpression();
	if(node != NULL)
	{
		returnNode = new ExpressionTreeNode();
		node->setParent(returnNode);
		returnNode->addChild(node);

		s = RelOp();
		if(s != NullSym)
		{
			node = new ExpressionTreeNode(s);
			node->setParent(returnNode);
			returnNode->addChild(node);

			node = SimpleExpression();
			if(node != NULL)
			{
				node->setParent(returnNode);
				returnNode->addChild(node);
				return returnNode;
			}
			else
			{
				delete node;
				return false;
			}
		}
		else
		{
			//w.execute();
			return node;
		}
	}
	
	return false;
}

ExpressionTreeNode* SyntaxAnalyzer::SimpleExpression()
{
	SymbolType s;

	ExpressionTreeNode* node;
	ExpressionTreeNode* returnNode;

	node = OrExpression();
	if(node != NULL)									//OrExpr
	{
		returnNode = new ExpressionTreeNode();
		node->setParent(returnNode);
		returnNode->addChild(node);

		for(int i=0; ; i++)
		{
			s = OrOp();
			if(s != NullSym)								//OrOp
			{
				node = new ExpressionTreeNode(s);
				node->setParent(returnNode);
				returnNode->addChild(node);

				node = OrExpression();
				if(node != NULL)							//OrExpr
				{
					node->setParent(returnNode);
					returnNode->addChild(node);
					
				}
				else
				{
					delete node;
					for(int i=0; i<returnNode->getChildrenCount(); i++)
					{
						delete returnNode->getChildAt(i);
					}
					return false;
				}
			}
			else
			{
				if(i == 0)
				{
					delete returnNode;
					return node;		//parent set to deleted object for a moment
				}
				else
					return returnNode;
			}
		}
	}

	return false;
}

ExpressionTreeNode* SyntaxAnalyzer::OrExpression()
{
	SymbolType s;
	ExpressionTreeNode* node;
	ExpressionTreeNode* returnNode;

	node = AndExpression();
	if(node != NULL)									//AndExpr
	{
		returnNode = new ExpressionTreeNode();
		node->setParent(returnNode);
		returnNode->addChild(node);

		
		for(int i=0; ; i++)
		{
			s = AndOp();
			if(s != NullSym)								//AndOp
			{
				node = new ExpressionTreeNode(s);
				node->setParent(returnNode);
				returnNode->addChild(node);

				node = AndExpression();
				if(node != NULL)							//AndExpr
				{
					node->setParent(returnNode);
					returnNode->addChild(node);
				}
				else
				{
					delete node;
					for(int i=0; i<returnNode->getChildrenCount(); i++)
					{
						delete returnNode->getChildAt(i);
					}
					return false;
				}
			}
			else
			{
				if(i == 0)
				{
					delete returnNode;
					return node;		//parent set to deleted object for a moment
				}
				else
					return returnNode;
			}
		}

	}
	else
		return false;
}

ExpressionTreeNode* SyntaxAnalyzer::AndExpression()
{
	FunInstruction* i;
	Fraction* f;
	ExpressionTreeNode* node;
	ExpressionTreeNode* returnNode;


	if(currentSymbol.getSymbolType() == NotSym)						// !
	{	
		returnNode = new ExpressionTreeNode(NotSym);
		advance();

		node = AndExpression();										//AndExpr
		if(node)
		{
			node->setParent(returnNode);
			returnNode->addChild(node);
			return returnNode;
		}
		else
		{
			delete returnNode;
			return false;
		}
	}

	if(currentSymbol.getSymbolType() == IdentSym)					//id
	{
		returnNode = new ExpressionTreeNode(new Variable(currentSymbol.getValue()));
		advance();
		return returnNode;
	}

	f = FractConst();
	if(f != NULL)													//fract
	{
		returnNode = new ExpressionTreeNode(new Value(f));
		return returnNode;
	}

	if(currentSymbol.getSymbolType() == BoolValSym)					//boolVal
	{
		if(currentSymbol.getValue() == "true")
			returnNode = new ExpressionTreeNode(new Value(true));
		else
			returnNode = new ExpressionTreeNode(new Value(false));
		advance();
		return returnNode;
	}

	i = FunCall();
	if(i != NULL)													//funCall
	{
		returnNode = new ExpressionTreeNode(i);
		return returnNode;
	}
	if(currentSymbol.getSymbolType() == LBracketSym)				//(
	{
		advance();
		node = Expression();
		if(node != NULL)											//expr
		{
			if(currentSymbol.getSymbolType() == RBracketSym)		//)
			{
				
				advance();
				return node;
			}
			else
			{
				delete node;
				errorInfo("')'");
				return false;
			}
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

SymbolType SyntaxAnalyzer::RelOp()
{
	if(currentSymbol.getSymbolType() == LessEqSym)
	{
		advance();
		return LessEqSym;
	}
	if(currentSymbol.getSymbolType() == GreaterEqSym)
	{
		advance();
		return GreaterEqSym;
	}
	if(currentSymbol.getSymbolType() == GreaterSym)
	{
		advance();
		return GreaterSym;
	}
	if(currentSymbol.getSymbolType() == LessSym)
	{
		advance();
		return LessSym;
	}
	if(currentSymbol.getSymbolType() == EqualSym)
	{
		advance();
		return EqualSym;
	}
	if(currentSymbol.getSymbolType() == NotEqualSym)
	{
		advance();
		return NotEqualSym;
	}
	//errorInfo("relation-type operator");
	return NullSym;
}

SymbolType SyntaxAnalyzer::AndOp()
{
	if(currentSymbol.getSymbolType() == MultiSym)
	{
		advance();
		return MultiSym;
	}
	if(currentSymbol.getSymbolType() == DivideSym)
	{
		advance();
		return DivideSym;
	}
	if(currentSymbol.getSymbolType() == AndSym)
	{
		advance();
		return AndSym;
	}
	//errorInfo("and-type operator");
	return NullSym;
}

SymbolType SyntaxAnalyzer::OrOp()
{
	if(currentSymbol.getSymbolType() == PlusSym)
	{
		advance();
		return PlusSym;
	}
	if(currentSymbol.getSymbolType() == MinusSym)
	{
		advance();
		return MinusSym;
	}
	if(currentSymbol.getSymbolType() == OrSym)
	{
		advance();
		return OrSym;
	}
	//errorInfo("or-type operator");
	return NullSym;
}

pair<bool, vector<string> > SyntaxAnalyzer::Params()
{
	vector<string> params;
	if(currentSymbol.getSymbolType() == LBracketSym)							//(
	{
		advance();
		if(currentSymbol.getSymbolType() == RBracketSym)						//)
		{
			advance();
			return make_pair(true,params);
		}
		else if(currentSymbol.getSymbolType() == IdentSym)						//id
		{
			params.push_back(currentSymbol.getValue());
			advance();
			for(;;)																
			{
				if(currentSymbol.getSymbolType() == CommaSym)					//,
				{
					advance();
					if(currentSymbol.getSymbolType() == IdentSym)				//id
					{
						advance();
					}
					else
					{
						errorInfo("id");
						return make_pair(false,params);
					}
				}
				else
					break;
			}

			if(currentSymbol.getSymbolType() == RBracketSym)					//)
			{
				advance();
				return make_pair(true,params);
			}
			else
			{
				errorInfo("')'");
				return make_pair(false,params);
			}

			
		}
		else
		{
			errorInfo("id or ')'");
			return make_pair(false,params);
		}
	}
	else
	{
		errorInfo("'('");
		return make_pair(false,params);
	}

}

bool SyntaxAnalyzer::Block()
{
	Instruction* i;
	if(currentSymbol.getSymbolType() == LBraceSym)						//{
	{
		advance();
		if(currentSymbol.getSymbolType() == RBraceSym)					//}
		{
			advance();
			return true;
		}
		else														
		{
			for(;;)														//{Instruction | WhileStment | IfStment}
			{
					if(WhileStatement())
					{
						continue;
					}
					if(IfStatement())
					{
						continue;
					}
					i = InstructionS();
					if(i != NULL)
					{
						InstructionList.push_back(i);
						continue;
					}
					else break;
			}
			if(currentSymbol.getSymbolType() == RBraceSym)				//}
			{
				advance();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
		return false;
}

pair<ExpressionInstruction*, vector<Instruction*> > SyntaxAnalyzer::FunBlock()
{
	vector<Instruction*> instructions;
	Instruction* i;
	ExpressionTreeNode* node;
	ExpressionInstruction* e = NULL;

	if(currentSymbol.getSymbolType() == LBraceSym)					//{
	{
		advance();
													
		for(;;)														//{Instruction | WhileStment | IfStment}
		{
				if(WhileStatement())
				{
					continue;
				}
				if(IfStatement())
				{
					continue;
				}
				i = InstructionS();
				if(i != NULL)
				{
					instructions.push_back(i);
					continue;
				}
				else break;
		}
		if(currentSymbol.getSymbolType() == ReturnSym)				//return
		{
			advance();
			node = Expression();
			if(node != NULL)										//expression
			{
				if(currentSymbol.getSymbolType() == SemicolonSym)	//;
				{
					int line = lexAnalyzer->getRow();				//line can change after ';'
					advance();
					if(currentSymbol.getSymbolType() == RBraceSym)	//}
					{
						
						e = new ExpressionInstruction(node);
						e->setLine(line);							
						advance();
						return make_pair(e, instructions);
					}
					else
					{
						errorInfo("}");
						return make_pair(e, instructions);
					}
				}
				else
				{
					errorInfo(";");
					return make_pair(e, instructions);
				}
			}
			else
			{
				return make_pair(e, instructions);
			}
		}
		else
		{
			errorInfo("return");
			return make_pair(e, instructions);
		}			
	}
	else
		return make_pair(e, instructions);
}

Instruction* SyntaxAnalyzer::InstructionS()
{
	Instruction* i;
	ExpressionTreeNode* node;


	i = FunCall();
	if(i != NULL)
	{
		if(currentSymbol.getSymbolType() == SemicolonSym)
		{
			advance();
			return i;
		}
		else
		{
			errorInfo("';'");
			return false;
		}
	}

	if(currentSymbol.getSymbolType() == IdentSym)
	{
		string var = currentSymbol.getValue();
		advance();
		
		
		
		if(currentSymbol.getSymbolType() == SemicolonSym)			//declaration
		{
			
			DeclarationInstruction* d = new DeclarationInstruction(var);
			d->setLine(lexAnalyzer->getColumn());

			//InstructionList.pu
			advance();
			return d;
		}
		if(currentSymbol.getSymbolType() == AssigmentSym)			//assigment
		{
			advance();
			node = Expression();
			if(node != NULL)
			{
				if(currentSymbol.getSymbolType() == SemicolonSym)
				{
					
					ExpressionInstruction* e = new ExpressionInstruction(node);
					e->setLine(lexAnalyzer->getRow());
					AssigmentInstruction* a = new AssigmentInstruction(var, e);
					a->setLine(lexAnalyzer->getRow());
					advance();
					return a;
				}
				else
				{
					errorInfo("';'");
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	i = PrintCall();			
	if(i != NULL)				//TODO:zwraca cos printcall
	{
		return i;
	}
	return false;
}

FunInstruction* SyntaxAnalyzer::FunCall()
{
	FunInstruction* f;
	string id;
	pair<bool, vector<string> > paramsReturn;

	if(currentSymbol.getSymbolType() == CaretSym)
	{
		advance();
		if(currentSymbol.getSymbolType() == IdentSym)
		{
			id = currentSymbol.getValue();
			advance();

			paramsReturn = Params();
			if(paramsReturn.first)
			{
				//f.execute();
				f = new FunInstruction(id, paramsReturn.second);
				f->setLine(lexAnalyzer->getRow());
				return f;
			}
			else
			{
				return false;
			}
		}
		else
		{
			errorInfo("id");
			return false;
		}
	}
	else
	{
		return false;
	}
}

Instruction* SyntaxAnalyzer::PrintCall()
{
	PrintInstruction* p;
	ExpressionTreeNode* node;
	string text;
	bool isText;

	if(currentSymbol.getSymbolType() == PrintSym)							//print
	{
		advance();
		if(currentSymbol.getSymbolType() == LBracketSym)					//(
		{
			advance();
			node = Expression();
			if(node != NULL)												//expr												
			{
				//text = currentSymbol.getValue();
				isText = 0;
			}
			else if(currentSymbol.getSymbolType() == TextSym)				//text
			{
				text = currentSymbol.getValue();
				isText = 1;
				advance();
			}
			
			if(currentSymbol.getSymbolType() == RBracketSym)				//)
			{
				advance();
				if(currentSymbol.getSymbolType() == SemicolonSym)			//;
				{
					
					if(isText)
						p = new PrintInstruction(text);		//TODO: zmienic konstruktor
					else
					{
						ExpressionInstruction* e = new ExpressionInstruction(node);
						e->setLine(lexAnalyzer->getRow());
						p = new PrintInstruction(e);
					}
					p->setLine(lexAnalyzer->getRow());

					advance();
					return p;
				}
				else
				{
					errorInfo("';'");
					return false;
				}
				
			}
			else
			{
				errorInfo("')'");
				return false;
			}
		}
		else
		{
			errorInfo("'('");
			return false;
		}
	}
	else
	{
		return false;
	}
}
Fraction* SyntaxAnalyzer::FractConst()
{
	stringstream fractStream;
	if(currentSymbol.getSymbolType() == MinusSym)						//-
	{
		fractStream << currentSymbol.getValue();
		advance();	 
	}

	if(currentSymbol.getSymbolType() == IntegerSym)						//int
	{
		fractStream << currentSymbol.getValue();
		advance();
		if(currentSymbol.getSymbolType() == DotSym)						//.
		{
			fractStream << currentSymbol.getValue();
			advance();
			if(currentSymbol.getSymbolType() == IntegerSym)				//int
			{
				fractStream << currentSymbol.getValue();
				advance();
				if(currentSymbol.getSymbolType() == DivideSym)			// /
				{
					fractStream << currentSymbol.getValue();
					advance();
					if(currentSymbol.getSymbolType() == IntegerSym)		//int
					{
						fractStream << currentSymbol.getValue();
						advance();
						Fraction* f = new Fraction(fractStream.str());
						//cout << f->toString() << endl;
						return f;
					}
					else
					{
						errorInfo("integer");
						return false;
					}

					}
				else
				{
					errorInfo("'/'");
					return false;
				}
			}
			else
			{
				errorInfo("integer");
				return false;
			}

		}
		else
		{
			Fraction* f = new Fraction(fractStream.str());
			//cout << f.toString() << endl;
			return f;
		}
	}
	else
	{
		return false;
	}
}