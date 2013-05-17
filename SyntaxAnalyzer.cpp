#include "SyntaxAnalyzer.h"
#include "AssigmentInstruction.h"
#include "DeclarationInstruction.h"
#include "ExpressionInstruction.h"
#include "FunDeclarationInstruction.h"
#include "FunInstruction.h"
#include "IfInstruction.h"
#include "PrintInstruction.h"
#include "WhileInstruction.h"

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
	if(Statement())
		return true;
	else if(InstructionS())
		return true;
	else 
	{
		errorInfo("statement or instruction");
		return false;
	}

}

bool SyntaxAnalyzer::Statement()
{
	if(WhileStatement())
	{
		return true;
	}
	else if(IfStatement())
	{
		return true;
	}
	else if(FunStatement())
	{
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

bool SyntaxAnalyzer::FunStatement()
{
	FunDeclarationInstruction w;
	if(currentSymbol.getSymbolType() == FunctionSym)				//function
	{
		advance();
		if(currentSymbol.getSymbolType() == IdentSym)				//ident
		{
			advance();
			if(Params())											//params
			{				
				if(FunBlock())										//funblock
				{
					w.execute();
					return true;				
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

bool SyntaxAnalyzer::Expression()  //TODO:zwraca
{
	ExpressionInstruction w;
	if(SimpleExpression())
	{
		if(RelOp())
		{
			if(SimpleExpression())
			{
				w.execute();
				return true;
			}
			else
				return false;
		}
		else
		{
			w.execute();
			return true;
		}
	}
	else
		return false;
}

bool SyntaxAnalyzer::SimpleExpression()
{
	if(AndExpression())
	{
		if(AndOp())
		{
			if(AndExpression())
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			return true;
		}
	}
	else
		return false;
}

bool SyntaxAnalyzer::AndExpression()
{
	if(OrExpression())
	{
		if(OrOp())
		{
			if(OrExpression())
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			return true;
		}
	}
	else
		return false;
}

bool SyntaxAnalyzer::OrExpression()
{
	if(currentSymbol.getSymbolType() == NotSym)
	{
		advance();
		{
			if(OrExpression())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else if(currentSymbol.getSymbolType() == IdentSym)
	{
		advance();
		return true;
	}
	else if(FractConst())
	{
		return true;
	}
	else if(currentSymbol.getSymbolType() == BoolValSym)
	{
		advance();
		return true;
	}
	else if(FunCall())
	{
		return true;
	}
	else if(currentSymbol.getSymbolType() == LBracketSym)
	{
		advance();
		if(Expression())
		{
			if(currentSymbol.getSymbolType() == RBracketSym)
			{
				advance();
				return true;
			}
			else
			{
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

bool SyntaxAnalyzer::RelOp()
{
	if(currentSymbol.getSymbolType() == LessEqSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == GreaterEqSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == GreaterSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == LessSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == EqualSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == NotEqualSym)
	{
		advance();
		return true;
	}
	//errorInfo("relation-type operator");
	return false;
}

bool SyntaxAnalyzer::AndOp()
{
	if(currentSymbol.getSymbolType() == MultiSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == DivideSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == AndSym)
	{
		advance();
		return true;
	}
	//errorInfo("and-type operator");
	return false;
}

bool SyntaxAnalyzer::OrOp()
{
	if(currentSymbol.getSymbolType() == PlusSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == MinusSym)
	{
		advance();
		return true;
	}
	if(currentSymbol.getSymbolType() == OrSym)
	{
		advance();
		return true;
	}
	//errorInfo("or-type operator");
	return false;
}

bool SyntaxAnalyzer::Params()
{
	if(currentSymbol.getSymbolType() == LBracketSym)							//(
	{
		advance();
		if(currentSymbol.getSymbolType() == RBracketSym)						//)
		{
			advance();
			return true;
		}
		else if(currentSymbol.getSymbolType() == IdentSym)						//id
		{
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
						return false;
					}
				}
				else
					break;
			}

			if(currentSymbol.getSymbolType() == RBracketSym)					//)
			{
				advance();
				return true;
			}
			else
			{
				errorInfo("')'");
				return false;
			}

			
		}
		else
		{
			errorInfo("id or ')'");
			return false;
		}
	}
	else
	{
		errorInfo("'('");
		return false;
	}

}

bool SyntaxAnalyzer::Block()
{
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
					if(InstructionS())
					{
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

bool SyntaxAnalyzer::FunBlock()
{
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
					if(InstructionS())
					{
						continue;
					}
					else break;
			}
			if(currentSymbol.getSymbolType() == ReturnSym)				//return
			{
				advance();
				if(Expression())										//expression
				{
					if(currentSymbol.getSymbolType() == SemicolonSym)	//;
					{
						advance();
						if(currentSymbol.getSymbolType() == RBraceSym)	//}
						{
							advance();
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						errorInfo(";");
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				errorInfo("return");
				return false;
			}			
		}
	}
	else
		return false;
}

bool SyntaxAnalyzer::InstructionS()
{
	if(FunCall())
	{
		if(currentSymbol.getSymbolType() == SemicolonSym)
		{
			advance();
			return true;
		}
		else
		{
			errorInfo("';'");
			return false;
		}
	}

	if(currentSymbol.getSymbolType() == IdentSym)
	{
		advance();
		AssigmentInstruction a;
		DeclarationInstruction d;
		if(currentSymbol.getSymbolType() == SemicolonSym)			//declaration
		{
			advance();
			d.execute();
			return true;
		}
		if(currentSymbol.getSymbolType() == AssigmentSym)				//assigment
		{
			advance();
			if(Expression())
			{
				if(currentSymbol.getSymbolType() == SemicolonSym)
				{
					advance();
					a.execute();
					return true;
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
	if(PrintCall())
	{
		return true;
	}
	return false;
}

bool SyntaxAnalyzer::FunCall()
{
	FunInstruction f;
	if(currentSymbol.getSymbolType() == CaretSym)
	{
		advance();
		if(currentSymbol.getSymbolType() == IdentSym)
		{
			advance();
			if(Params())
			{
				f.execute();
				return true;
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

bool SyntaxAnalyzer::PrintCall()
{
	PrintInstruction p;
	if(currentSymbol.getSymbolType() == PrintSym)							//print
	{
		advance();
		if(currentSymbol.getSymbolType() == LBracketSym)					//(
		{
			advance();
			if(currentSymbol.getSymbolType() == IdentSym)					//id
			{
				advance();
			}
			else if(currentSymbol.getSymbolType() == TextSym)				//text
			{
				advance();
			}
			
			if(currentSymbol.getSymbolType() == RBracketSym)					//)
			{
				advance();
				if(currentSymbol.getSymbolType() == SemicolonSym)			//;
				{
					advance();
					p.execute();
					return true;
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
bool SyntaxAnalyzer::FractConst()
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
						Fraction f(fractStream.str());
						cout << f.toString() << endl;
						return true;
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
			Fraction f(fractStream.str());
			cout << f.toString() << endl;
			return true;
		}
	}
	else
	{
		return false;
	}
}