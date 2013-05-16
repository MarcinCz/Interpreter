#include "Fraction.h"
#include <sstream>

Fraction::Fraction(void)
{
}

Fraction::Fraction(int _integer, int _numerator, int _denominator, bool _sign)
{
	integer = _integer;
	numerator = _numerator;
	denominator = _denominator;
	sign = _sign;
	normalize();
}

Fraction::~Fraction(void)
{
	
}

void Fraction::normalize()
{
	if(numerator == 0)
		denominator =0;

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
}

int Fraction::NWD(int a, int b)
{
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