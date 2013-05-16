#include <iostream>
#include "SourceReader.h"
#include "LexicalAnalyzer.h"
#include "Fraction.h"
#include <sstream>

int main(int argc, char *argv[])
{
	/*SourceReader sr;
	sr.openSource("dane.txt");
	LexicalAnalyzer la(&sr);
	Symbol s(AndSym, "a",1,1);
	while(s.getSymbolType()!=EOFSym)
	{
		s=la.getNextSymbol();
		cout<< s.getSymbolType() <<": "<<s.getValue()<<endl;
	}*/
	
	//char r='a';
	//while(r != EOF)
	//{
	//	r=sr.getNextChar();
	//	cout<<r<<endl;
	//}

	//std::stringstream s;
	//s<<EOF;
	//cout << s.str();

	Fraction f1(1,2,3);
	Fraction f2(2,3,4,false);
	std::cout<<(f2>=f1)<<endl;
	std::cout<<(f2<=f1)<<endl;
	std::cout<<(f1>=f1)<<endl;
	std::cout<<(f1<=f1)<<endl;
}