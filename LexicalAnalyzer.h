#pragma once

#include "SourceReader.h"


enum SymbolType
{
	IdentSym,		// identifier			0
	IntegerSym,		// integer				1
	TextSym,		// "text"				2

	//keywords
	BoolValSym,		// true, false			3
	WhileSym,		// while				4
	IfSym,			// if					5
	ElseSym,		// else					6
	FunctionSym,	// function				7
	ReturnSym,		// return				8
	PrintSym,		// print				9

	//operators
	PlusSym,		// +					10
	MinusSym,		// -					11
	OrSym,			// or					12
	MultiSym,		// *					13
	DivideSym,		// /					14
	AndSym,			// and					15
	GreaterSym,		// >					16
	LessSym,		// <					17
	EqualSym,		// ==					18
	NotEqualSym,	// !=					19
	GreaterEqSym,	// >=					20
	LessEqSym,		// <=					21
	AssigmentSym,	// =					22
	NotSym,			// !					23

	//special
	DotSym,			// .					24
	CommaSym,		// ,					25
	SemicolonSym,	// ;					26
	LBraceSym,		// {					27
	RBraceSym,		// }					28
	LBracketSym,	// (					29
	RBracketSym,	// )					30
	CaretSym,		// ^					31

	EOFSym,			// no more symbols		32
	UnknownSym		// unknown				33

};

class Symbol
{
public:
	Symbol();
	Symbol(SymbolType type, string value, int column, int row);
	Symbol(SymbolType type, string value, int column, int row, string errorInfo);
	~Symbol();

	void setPosition(int column, int row);
	pair<int,int> getPosition();
	SymbolType getSymbolType();
	string getValue();


private:
	string errorInfo;
	SymbolType type;
	string value;
	int column;
	int row;
};

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(void);
	LexicalAnalyzer(SourceReader* srcReader);
	~LexicalAnalyzer(void);

	Symbol getNextSymbol();
	//void setSourceReader();

private:
	char currentChar;
	SourceReader* srcReader;
};

