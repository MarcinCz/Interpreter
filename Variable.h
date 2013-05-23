#pragma once
#include "LexicalAnalyzer.h"
#include "Fraction.h"

enum VarType{
	FractType,
	BoolType,
	UnknownType
};

class Value{
public:
	Value() {}
	Value(const Value *f)
	{
		type = f->type;
		value = f->value;
	}
	Value(VarType _type, string _value)
	{
		type = _type;
		value = _value;
	}
	Value(bool _boolVal)
	{
		type = BoolType;
		if(_boolVal) value = "true";
		else value = "false";
		type = BoolType;
	}
	Value(Fraction* _fractVal)
	{
		type = FractType;
		value = _fractVal->toString();
	}
	~Value(){ /*if(type = FractType) delete fractVal;*/}

	bool isFraction() { return type == FractType; }
	bool isBool() { return type == BoolType; }
	bool isUnknown() { return type == UnknownType; }

	VarType getType() { return type; }
	string toString() { return value; }
	void setType(VarType _type) { type =_type; }
	void setValue(string _value) { value =_value; } 
	void setValue(Fraction _fractVal) { value = _fractVal.toString(); type = FractType; }
	void setValue(bool _boolVal) 
	{ 
		if(_boolVal) value = "true";
		else value = "false";
		type = BoolType; 
	}
	
	//Fraction *getFraction() { return fractVal; }
	//bool getBool() { return boolVal; }
	Fraction toFraction() { return Fraction(value); }
	bool toBool() { return (value == "true"); }  //TODO: moze zamiana fract<->bool
	/*string toString() 
	{
		if(type == BoolType)
		{
			if(boolVal)
				return "true";
			else
				return "false";
		}
		else
		{
			return fractVal->toString();
		}
	}*/

private:
	VarType type;
	string value;
	//Fraction* fractVal;
	//bool boolVal;
	
};


class Variable
{
public:
	Variable(void) {}
	Variable(string _name){ name = _name; value = &Value(UnknownType, ""); }
	~Variable(void) {}

	Value* getValue() { return value; }
	string getName() { return name; }
	int getLevel() {return level;}

	void setValue(Value* _value) { value = _value; }
	void setName(string _name) { name = _name; }
	void setLevel(int _level) {level = _level;}
		

private:
	string name;
	Value* value;
	int level;			//variable stack level
};

