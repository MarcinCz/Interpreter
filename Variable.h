#pragma once
#include "SyntaxAnalyzer.h"

enum VarType{
	FractType,
	BoolType,
	UnknownType
};

class Value{
public:
	Value() {}
	Value(VarType _type, string _value)
	{
		type = _type;
		value = _value;
	}
	Value(bool _boolVal)
	{
		type = BoolType;
		boolVal = _boolVal;
	}
	Value(Fraction* _fractVal)
	{
		type = FractType;
		fractVal = _fractVal;
	}
	~Value(){}

	bool isFraction() { return type == FractType; }
	bool isBool() { return type == BoolType; }
	bool isUnknown() { return type == UnknownType; }

	VarType getType() { return type; }
	string getValue() { return value; }
	void setType(VarType _type) { type =_type; }
	void setValue(string _value) { value =_value; } 
	//void setValue(Fraction _fractVal) { fractVal = _fractVal; }
	//void setValue(bool _boolVal) { boolVal = _boolVal; }
	
	Fraction *getFraction() { return fractVal; }
	bool getBool() { return boolVal; }
	Fraction toFraction() { return Fraction(value); }
	bool toBool() { return (value == "true"); }  //TODO: moze zamiana fract<->bool


private:
	VarType type;
	string value;
	Fraction* fractVal;
	bool boolVal;
};


class Variable
{
public:
	Variable(void) {}
	Variable(string _name){ name = _name; value = Value(UnknownType, ""); }
	~Variable(void) {}

	Value getValue() { return value; }
	string getName() { return name; }
	void setValue(Value _value) { value = _value; }
	void setName(string _name) { name = _name; }

private:
	string name;
	Value value;
};

