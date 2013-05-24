#include "Fraction.h"
#include <sstream>

Fraction::Fraction(void)
{
	integer = 0;
	numerator = 0;
	denominator = 1;
	sign = true;
}

Fraction::Fraction(const Fraction &f)
{
	sign = f.sign;
	integer = f.integer;
	denominator = f.denominator;
	numerator = f.numerator;

}
Fraction::Fraction(int _integer, int _numerator, int _denominator, bool _sign)
{
	integer = _integer;
	numerator = _numerator;
	denominator = _denominator;
	sign = _sign;
	normalize();
}

Fraction::Fraction(string _value)
{
	sign = true;
	numerator = 0;
	denominator = 1;

	unsigned pos = _value.find('-');
	if(pos!=string::npos)  //negative
	{
		sign = false;
		_value=_value.substr(1,_value.size()-1);
	}
	pos = _value.find('.');
	if(pos == string::npos)  //only integer
	{
		stringstream(_value) >> integer;
	}
	else
	{
		string intS = _value.substr(0,pos);
		stringstream(intS) >> integer;
		string restS = _value.substr(pos+1, _value.size()-pos-1);
		pos = restS.find('/');
		string numS = restS.substr(0,pos);
		stringstream(numS) >> numerator;;
		string denS = restS.substr(pos+1, restS.size()-pos-1);
		stringstream(denS) >> denominator;

	}

}
Fraction::~Fraction(void)
{
	
}

void Fraction::normalize()
{
	

	if(denominator != 0)
	{
		int nwd = NWD(numerator, denominator);
		numerator = numerator/nwd;
		denominator = denominator/nwd;

		if(numerator >= denominator)
		{
			int newInt = (int)(numerator/denominator);
			integer += newInt;
			numerator -= newInt * denominator;
		}
	}

	/*if(numerator == 0)
		denominator = 1;*/

	if(isZero())
	{
		sign = true;
	}
}

int Fraction::NWD(int a, int b)
{
	if(a==0 || b==0)
		return 1;

	while (a!=b) 
	{
		if (a>b)
			a-=b; 
		else
			b-=a; 
	}
	return a;
}

int Fraction::NWW(int a, int b)
{
	return (a*b)/NWD(a,b);
}

bool Fraction::isZero()
{
	if(integer == 0 && numerator == 0)
		return true;
	else
		return false;
}

bool Fraction::isDenominatorZero()
{
	return denominator==0;
}

string Fraction::toString()
{
	stringstream sstr;
	if(!sign) sstr << '-';

	sstr << integer;

	if(numerator != 0)
	{
		sstr << '.';
		sstr << numerator;
		sstr << '/';
		sstr << denominator;
	}

	return sstr.str();
}


bool Fraction::operator ==(const Fraction &f) const
{
	return (integer == f.integer && numerator == f.numerator && denominator == denominator && sign == f.sign) 
		|| (integer == 0 && numerator == 0 && f.integer == 0 && f.numerator == 0);
}

bool Fraction::operator !=(const Fraction &f) const
{
	return !(*this == f);
}

bool Fraction::operator >(const Fraction &f) const
{
	if(*this == f)
		return false;

	if(sign && !f.sign)
		return true;
	if(!sign && f.sign)
		return false;

	if(integer > f.integer)
	{
		if(sign)
			return true;
		else 
			return false;
	}
	else if(integer < f.integer)
	{
		if(sign)
			return false;
		else 
			return true;
	}
	else if(numerator * f.denominator > f.numerator * denominator)
	{
		
		if(sign)
			return true;
		else 
			return false;
	}
	else
	{
		if(sign)
			return false;
		else 
			return true;
	}

}

bool Fraction::operator <(const Fraction &f) const
{
	return (!(*this > f) && *this != f);
}
bool Fraction::operator >=(const Fraction &f) const
{
	return *this == f || *this > f;
}

bool Fraction::operator <=(const Fraction &f) const
{
	return *this == f || *this < f;
}

Fraction Fraction::operator +(const Fraction &f)
{
	Fraction returned;
	Fraction f1 = *this;
	Fraction f2 = f;
	int nww = NWW(f1.denominator, f2.denominator);


	if(f1.sign == f2.sign)	//same signs
	{
		returned.integer = f1.integer + f2.integer;
		returned.sign = f1.sign;
		returned.numerator = (f1.numerator * (nww/f1.denominator)) + (f2.numerator * (nww/f2.denominator));
		returned.denominator = nww;
		returned.normalize();

		return returned;
	}
	else					//different signs
	{
		if(f1.sign)			//positive + negative
		{
			Fraction f2m = f2;
			f2m.sign = true;

			if(f1 > f2m)		//positive larger
			{
				returned.sign = true;

				if(f1.numerator*f2.denominator >= f2.numerator*f1.denominator)
				{
					returned.numerator = (f1.numerator * (nww/f1.denominator)) - (f2.numerator * (nww/f2.denominator));
					returned.denominator = nww;
					returned.integer = f1.integer - f2.integer;
				}
				else
				{
					returned.numerator = nww + (f1.numerator * (nww/f1.denominator)) - (f2.numerator * (nww/f2.denominator));
					returned.denominator = nww;
					returned.integer = f1.integer - f2.integer - 1;
				}
			}
			else
			{
				returned.sign = false;

				if(f2.numerator*f1.denominator >= f1.numerator*f2.denominator)
				{
					returned.numerator = (f2.numerator * (nww/f2.denominator)) - (f1.numerator * (nww/f1.denominator));
					returned.denominator = nww;
					returned.integer = f2.integer - f1.integer;
				}
				else
				{
					returned.numerator = nww + (f2.numerator * (nww/f2.denominator)) - (f1.numerator * (nww/f1.denominator));
					returned.denominator = nww;
					returned.integer = f2.integer - f1.integer - 1;
			
				}
			}
		}
		else
			returned = f2+f1;

		returned.normalize();
		return returned;
	}

}

Fraction Fraction::operator -(const Fraction &f)// const
{
	Fraction returned;

	Fraction fm = f;
	fm.sign = !f.sign;

	returned = *this + fm;
	return returned;
}

Fraction Fraction::operator *(const Fraction &f)
{
	Fraction returned;
	
	returned.integer = 0;


	returned.numerator = (integer * denominator + numerator) * (f.integer * f.denominator + f.numerator);
	returned.denominator = denominator * f.denominator;
	returned.normalize();
	returned.sign = (sign==f.sign);
	
	return returned;

}

Fraction Fraction::operator /(const Fraction &f)
{
	Fraction returned;
	Fraction f1 = *this;
	Fraction f2 = f;

	if(f2.isZero())
	{
		//TODO: dzielenie przez zero
		return returned;
	}
	returned.integer = 0;
	returned.numerator = (f1.integer * f1.denominator + f1.numerator) * f2.denominator;
	returned.denominator = (f2.integer * f2.denominator + f2.numerator) * f1.denominator;
	returned.normalize();
	returned.sign = (sign==f.sign);
	
	return returned;
}