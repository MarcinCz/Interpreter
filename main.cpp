#include <iostream>
#include "SourceReader.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Interpreter.h"
#include "Variable.h"
#include "Fraction.h"
#include <sstream>

int main(int argc, char *argv[])
{
	SourceReader sr;
	sr.openSource("dane.txt");
	LexicalAnalyzer* la = new LexicalAnalyzer(&sr);
	Symbol s(AndSym, "a",1,1);
	/*while(s.getSymbolType()!=EOFSym)
	{
		s=la->getNextSymbol();
		cout<< s.getSymbolType() <<": "<<s.getValue()<< " c:"<<s.getPosition().first <<" r:"<< s.getPosition().second<<endl;
	}*/
	
	SyntaxAnalyzer sa(la);
	sa.Program();

	//Instruction i(IfInstr);
	//AssigmentInstruction a;
	//a.setType(AssigmentInst);
	//cout << a.getType() <<endl;

	/*char r='a';
	while(r != EOF)
	{
		r=sr.getNextChar();
		cout<<r<<" c:"<<sr.getPosition().first <<" r:"<< sr.getPosition().second<<endl;
	}*/

	//std::stringstream s;
	//s<<EOF;
	//cout << s.str();

	//Fraction f1("");
	//Fraction f2(2,3,4,false);
	///*std::cout<<(f1.toString())<<endl;
	//std::cout<<(f2<=f1)<<endl;
	//std::cout<<(f1>=f1)<<endl;
	//std::cout<<(f1<=f1)<<endl;*/

	//Value v = Value(BoolType,"true");
	//std::cout<<v.toBool()<<endl;
	//std::cout<<v.getType()<<endl;

	//Variable var("asd");
	//var.setValue(v);
	//std::cout<<var.getValue().toBool()<<endl;



	/*Interpreter i;
	i.increaseStackLevel();
	i.increaseStackLevel();*/

	/*vector< vector <int> > v;
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	vector<int> b;
	b.push_back(3);
	b.push_back(4);

	v.push_back(a);
	v.push_back(b);

	cout << v.at(0).at(0);*/
	
	
	
	cout << "asd";
}