#include "LexicalAnalyzer.h"
#include <sstream>

/*
****Symbol****
*/
Symbol::Symbol(void)
{
}

Symbol::Symbol(SymbolType _type, string _value, int _column, int _row)
{
	type = _type;
	value = _value;
	column = _column;
	row = _row;
}

Symbol::Symbol(SymbolType _type, string _value, int _column, int _row, string _errorInfo)
{
	type = _type;
	value = _value;
	column = _column;
	row = _row;
	errorInfo = _errorInfo;
}

Symbol::~Symbol()
{
}

void Symbol::setPosition(int _column, int _row)
{
	column = _column;
	row = _row;
}

pair<int,int> Symbol::getPosition()
{
	return make_pair(column,row);
}

SymbolType Symbol::getSymbolType()
{
	return type;
}

string Symbol::getValue()
{
	return value;
}


/*
****LexicalAnalyzer****
*/

LexicalAnalyzer::LexicalAnalyzer(void)
{
	currentChar = srcReader->getNextChar();
}


LexicalAnalyzer::~LexicalAnalyzer(void)
{

}

LexicalAnalyzer::LexicalAnalyzer(SourceReader* _srcReader)
{
	srcReader = _srcReader;
	currentChar = srcReader->getNextChar();		//first character
}

Symbol LexicalAnalyzer::getNextSymbol()
{
	stringstream symValue;

	pair<int,int> position = srcReader->getPosition();
	int column = position.first;
	int row = position.second;

	//end of file
	if(currentChar == EOF)
		return Symbol(EOFSym, symValue.str(), column, row);

	//white space 
	while(isspace(currentChar))
	{
		currentChar = srcReader->getNextChar();
		if(currentChar == EOF)
			return Symbol(EOFSym, symValue.str(), column, row);
	}

	//integer
	if(isdigit(currentChar))
	{
		if(currentChar == '0')
		{
			symValue << '0';
			currentChar = srcReader->getNextChar();
			return Symbol(IntegerSym,symValue.str(), column, row);
		}

		while(isdigit(currentChar))
		{
			symValue << currentChar;
			currentChar = srcReader->getNextChar();
		}
		//currentChar = srcReader->getNextChar();
		//char set after digits
		return Symbol(IntegerSym,symValue.str(), column, row);
	}
	//text
	if(currentChar == '"')
	{
		symValue << '"';
		currentChar = srcReader->getNextChar();
		

		while(currentChar != '"')
		{
			if(currentChar == EOF)
				return Symbol(UnknownSym,symValue.str(), column, row, "Unknown symbol. Expected closing '\"'");
			
			symValue << currentChar;
			currentChar = srcReader->getNextChar();
		}
		
		string textStr = symValue.str();
		textStr = textStr.substr(1,textStr.size()-1);		//text without ""
		currentChar = srcReader->getNextChar();				//char set after second "
		return Symbol(TextSym, textStr, column, row);
	}

	//operators, specials
	switch(currentChar)
	{
	case '.':
		currentChar = srcReader->getNextChar();
		return Symbol(DotSym,".", column, row);
	case ',':
		currentChar = srcReader->getNextChar();
		return Symbol(CommaSym,",", column, row);
	case '+':
		currentChar = srcReader->getNextChar();
		return Symbol(PlusSym,"+", column, row);
	case '-':
		currentChar = srcReader->getNextChar();
		return Symbol(MinusSym,"-", column, row);
	case '*':
		currentChar = srcReader->getNextChar();
		return Symbol(MultiSym,"*", column, row);
	case '/':
		currentChar = srcReader->getNextChar();
		return Symbol(DivideSym,"/", column, row);
	case '>':
		currentChar = srcReader->getNextChar();
		if(currentChar == '=')
		{
			currentChar = srcReader->getNextChar();
			return Symbol(GreaterEqSym,">=", column, row);
		}
		return Symbol(GreaterSym,">", column, row);
	case '<':
		currentChar = srcReader->getNextChar();
		if(currentChar == '=')
		{
			currentChar = srcReader->getNextChar();
			return Symbol(LessEqSym,"<=", column, row);
		}
		return Symbol(LessSym,"<", column, row);
	case '=':
		currentChar = srcReader->getNextChar();
		if(currentChar == '=')
		{
			currentChar = srcReader->getNextChar();
			return Symbol(EqualSym,"==", column, row);
		}
		return Symbol(AssigmentSym,"=", column, row);
	case '!':
		currentChar = srcReader->getNextChar();
		if(currentChar == '=')
		{
			currentChar = srcReader->getNextChar();
			return Symbol(NotEqualSym,"!=", column, row);
		}
		return Symbol(NotSym,"!", column, row);
	case ';':
		currentChar = srcReader->getNextChar();
		return Symbol(SemicolonSym,";", column, row);
	case '{':
		currentChar = srcReader->getNextChar();
		return Symbol(LBraceSym,"{", column, row);
	case '}':
		currentChar = srcReader->getNextChar();
		return Symbol(RBraceSym,"}", column, row);
	case '(':
		currentChar = srcReader->getNextChar();
		return Symbol(LBracketSym,"(", column, row);
	case ')':
		currentChar = srcReader->getNextChar();
		return Symbol(RBracketSym,")", column, row);
	case '#':
		currentChar = srcReader->getNextChar();
		if(currentChar == '#')
		{
			while(currentChar != '\n')
			{
				currentChar = srcReader->getNextChar();
			}
			return getNextSymbol();
		}
		return Symbol(UnknownSym,"#", column, row);
	case '^':
		currentChar = srcReader->getNextChar();
		return Symbol(CaretSym,"^", column, row);
	}

	//keywords, id
	if(isalnum(currentChar))
	{
		while(isalnum(currentChar))
		{
			symValue << currentChar;
			currentChar = srcReader->getNextChar();

		}
		string alnum = symValue.str();
		if(alnum == "true" || alnum == "false")
		{
			return Symbol(BoolValSym, alnum, column, row);
		}
		else if(alnum == "while")
		{
			return Symbol(WhileSym, alnum, column, row);
		}
		else if(alnum == "if")
		{
			return Symbol(IfSym, alnum, column, row);
		}
		else if(alnum == "else")
		{
			return Symbol(ElseSym, alnum, column, row);
		}
		else if(alnum == "function")
		{
			return Symbol(FunctionSym, alnum, column, row);
		}
		else if(alnum == "return")
		{
			return Symbol(ReturnSym, alnum, column, row);
		}
		else if(alnum == "print")
		{
			return Symbol(PrintSym, alnum, column, row);
		}
		else if(alnum == "and")
		{
			return Symbol(AndSym, alnum, column, row);
		}
		else if(alnum == "or")
		{
			return Symbol(OrSym, alnum, column, row);
		}
		else			//ident
		{
			return Symbol(IdentSym, alnum, column, row);
		}
	}

	symValue << currentChar;
	currentChar = srcReader->getNextChar();
	return Symbol(UnknownSym, symValue.str(), column, row, "Unknown symbol");
}