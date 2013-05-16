#pragma once
#include "SyntaxAnalyzer.h"

enum VarType{
	FractType,
	BoolType,
	UnknownType
};

class VarValue{
public:
	VarValue() {}
	VarValue(VarType _type, string _value)
	{
		type = _type;
		value = _value;
	}
	~VarValue(){}

	bool isFraction() { return type == FractType; }
	bool isBool() { return type == BoolType; }
	bool isUnknown() { return type == UnknownType; }

	VarType getType() { return type; }
	string getValue() { return value; }
	void setType(VarType _type) { type =_type; }
	void setValue(string _value) { value =_value; } 
	//void setValue(Fraction _fractVal) { fractVal = _fractVal; }
	//void setValue(bool _boolVal) { boolVal = _boolVal; }
	
	Fraction toFraction() { return Fraction(value); }
	bool toBool() { return (value == "true"); }  //TODO: moze zamiana fract<->bool


private:
	VarType type;
	string value;
	Fraction fractVal;
	bool boolVal;
};


class Variable
{
public:
	Variable(void);
	Variable(string _name){ name = _name; value = VarValue(UnknownType, ""); }
	~Variable(void);

	VarValue getValue() { return value; }
	string getName() { return name; }
	void setValue(VarValue _value) { value = _value; }
	void setName(string _name) { name = _name; }

private:
	string name;
	VarValue value;
};

