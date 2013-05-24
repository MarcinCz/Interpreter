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
		valueString = f->valueString;
	}
	Value(VarType _type, string _value)
	{
		type = _type;
		valueString = _value;
	}
	Value(bool _boolVal)
	{
		type = BoolType;
		if(_boolVal) valueString = "true";
		else valueString = "false";
		type = BoolType;
	}
	Value(Fraction* _fractVal)
	{
		type = FractType;
		valueString = _fractVal->toString();
	}
	Value(string _valueString)
	{
		valueString =_valueString;
	}
	~Value(){ /*if(type = FractType) delete fractVal;*/}

	bool isFraction() { return type == FractType; }
	bool isBool() { return type == BoolType; }
	bool isUnknown() { return type == UnknownType; }

	VarType getType() { return type; }
	string toString() { return valueString; }
	void setType(VarType _type) { type =_type; }
	void setValue(string _valueString) { valueString =_valueString; } 
	void setValue(Fraction _fractVal) { valueString = _fractVal.toString(); type = FractType; }
	void setValue(bool _boolVal) 
	{ 
		if(_boolVal) valueString = "true";
		else valueString = "false";
		type = BoolType; 
	}
	
	//Fraction *getFraction() { return fractVal; }
	//bool getBool() { return boolVal; }
	Fraction toFraction() { return Fraction(valueString); }
	bool toBool() { return (valueString == "true"); }  //TODO: moze zamiana fract<->bool
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
	string valueString;
	//Fraction* fractVal;
	//bool boolVal;
	
};


class Variable
{
public:
	Variable(void) {}
	Variable(string _name){ name = _name; value = new Value(UnknownType, ""); }
	Variable(string _name, Value* _val){name = _name; value = _val;}
	~Variable(void) { 
		delete value;
	}

	Value* getValue() { return value; }
	string getName() { return name; }
	int getLevel() { return level; }

	void setValue(Value* _value) { delete value, value = _value; }
	void setName(string _name) { name = _name; }
	void setLevel(int _level) {level = _level;}
		

private:
	string name;
	Value* value;
	int level;			//variable stack level
};

