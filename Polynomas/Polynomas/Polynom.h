#pragma once
#include "Monom.h"
#include "List.h"

class Polynom
{
	string polyString;
	TList<Monom> polynom;
public:
	Polynom(string _polyString);

	Polynom(const Polynom& poly);

	Polynom() {};

	~Polynom();
	bool isSign(char c);
	void addSpaces();
	void deleteSpaces();
	void parseStringToMonomas();

	string toString();
	

	Polynom& operator+=(const Polynom &poly);
	Polynom& operator-=(const Polynom &poly);
	Polynom& operator*=(const Polynom &poly); 
	void derivativeBy(char c);
	Polynom operator-() const;
	Polynom& operator= (const Polynom &poly);

	friend ostream& operator<<(ostream &os, Polynom &poly);
};

