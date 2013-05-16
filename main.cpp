#include <iostream>
#include "SourceReader.h"
#include "LexicalAnalyzer.h"
#include <sstream>

int main(int argc, char *argv[])
{
	SourceReader sr;
	sr.openSource("dane.txt");
	LexicalAnalyzer la(&sr);
	Symbol s(AndSym, "a",1,1);
	while(s.getSymbolType()!=EOFSym)
	{
		s=la.getNextSymbol();
		cout<< s.getSymbolType() <<": "<<s.getValue()<<endl;
	}
	
	//char r='a';
	//while(r != EOF)
	//{
	//	r=sr.getNextChar();
	//	cout<<r<<endl;
	//}

	//std::stringstream s;
	//s<<EOF;
	//cout << s.str();


}