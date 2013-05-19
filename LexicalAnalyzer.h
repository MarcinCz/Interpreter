#pragma once

#include "SourceReader.h"


enum SymbolType
{
	NullSym,		// nothing				0

	IdentSym,		// identifier			1
	IntegerSym,		// integer				2
	TextSym,		// "text"				3

	//keywords
	BoolValSym,		// true, false			4
	WhileSym,		// while				5
	IfSym,			// if					6
	ElseSym,		// else					7
	FunctionSym,	// function				8
	ReturnSym,		// return				9
	PrintSym,		// print				10

	//operators
	OrSym,			// or					11
	AndSym,			// and					12
	PlusSym,		// +					13
	MinusSym,		// -					14
	MultiSym,		// *					15
	DivideSym,		// /					16
	GreaterSym,		// >					17
	LessSym,		// <					18
	EqualSym,		// ==					19
	NotEqualSym,	// !=					20
	GreaterEqSym,	// >=					21
	LessEqSym,		// <=					22
	AssigmentSym,	// =					23
	NotSym,			// !					24

	//special
	DotSym,			// .					25
	CommaSym,		// ,					26
	SemicolonSym,	// ;					27
	LBraceSym,		// {					28
	RBraceSym,		// }					29
	LBracketSym,	// (					30
	RBracketSym,	// )					31
	CaretSym,		// ^					32

	EOFSym,			// no more symbols		33
	UnknownSym,		// unknown				34
	

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
	int getColumn();
	int getRow();
	//void setSourceReader();

private:
	char currentChar;
	SourceReader* srcReader;
};

