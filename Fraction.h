#pragma once

#include <string>

using namespace std;
class Fraction
{
public:
	Fraction(void);
	Fraction(int integer, int numerator, int denumeration, bool sign = true);
	~Fraction(void);

	bool isZero();
	string toString();

	Fraction& operator+(const Fraction& f);
	Fraction& operator-(const Fraction& f);
	Fraction& operator*(const Fraction& f);
	Fraction& operator/(const Fraction& f);
	
	/*Fraction& operator+=(const Fraction& f);
	Fraction& operator-=(const Fraction& f);
	Fraction& operator*=(const Fraction& f);
	Fraction& operator/=(const Fraction& f);*/

	bool operator==(const Fraction& f) const;
	bool operator!=(const Fraction& f) const;
	bool operator>(const Fraction& f) const;
	bool operator<(const Fraction& f) const;
	bool operator>=(const Fraction& f) const;
	bool operator<=(const Fraction& f) const;

private:
	int integer;
	int numerator;
	int denominator;

	bool sign;

	int NWD(int a, int b);
	int NWW(int a, int b);
	void normalize();
};

