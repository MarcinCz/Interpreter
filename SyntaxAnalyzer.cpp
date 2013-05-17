#include "SyntaxAnalyzer.h"
#include "AssigmentInstruction.h"
#include "DeclarationInstruction.h"
#include "ExpressionInstruction.h"
#include "FunDeclarationInstruction.h"
#include "FunInstruction.h"
#include "IfInstruction.h"
#include "PrintInstruction.h"
#include "WhileInstruction.h"

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
	cout<< "Expected "<<_info<<" at line:"<<currentSymbol.getPosition().second<<",column: "<<currentSymbol.getPosition().first<<endl;
}

bool SyntaxAnalyzer::Program()
{
	advance();

	while(currentSymbol.getSymbolType() == EOFSym)
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
	if(currentSymbol.getSymbolType() == WhileSym)					//if
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

bool SyntaxAnalyzer::Assigment()  //TODO. zwraca assigmentInstruction
{
	AssigmentInstruction w;
	if(currentSymbol.getSymbolType() == IdentSym)					//id
	{
		advance();
		if(currentSymbol.getSymbolType() == AssigmentSym)			//=
		{
			advance();
			if(Expression())										//expr
			{
				if(currentSymbol.getSymbolType() == SemicolonSym)	//;
				{
					w.execute();
					return true;
				}
				else
				{
					errorInfo("';'");
					return false;
				}
				
			}
			else
				return false;
		}
		else
		{
			errorInfo("'='");
			return false;
		}
	}
	else
		return false;
}

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