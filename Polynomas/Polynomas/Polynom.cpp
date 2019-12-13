#include "Polynom.h"



Polynom::Polynom(string _polyString): polyString(_polyString)
{
	deleteSpaces();
	addSpaces();
	Monom monom(-1);
	polynom.push(monom);
	parseStringToMonomas();
}

Polynom::Polynom(const Polynom& poly)
{
	Monom monom(-1);
	polynom.push(monom);
	auto start = polynom.pFirst;
	auto headInput = poly.polynom.pFirst;
	auto currNodeInput = poly.polynom.pFirst->next;
	while (currNodeInput->next != headInput){
		start = polynom.push_after(currNodeInput->data, start);
		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		 polynom.push_after(currNodeInput->data, start);
	}
	polyString = toString();
}

Polynom::~Polynom()
{

}

bool Polynom::isSign(char c)
{
	string signs = "+-";
	for (int i = 0; i < signs.length(); i++)
	{
		if (signs[i] == c)
			return true;
	}
	return false;
}

void Polynom::addSpaces()
{
	for (int i = 0; i < polyString.length(); i++)
	{
		if (isSign(polyString[i])) {
			if (i > 0 && polyString[i - 1] != ' ')
				polyString.insert(i++, " ");
			if (i < polyString.length() - 1 && polyString[i + 1] != ' ') {
				polyString.insert(i + 1, " ");
				i++;
			}
		}
	}
}

void Polynom::deleteSpaces()
{
	while (polyString.find(' ') != std::string::npos)
	{
		auto iter = polyString.find(' ');
		polyString.erase(polyString.find(' '), 1);
	}
}

void Polynom::parseStringToMonomas()
{
	string word;
	char sign = '+';
	for (stringstream is(polyString); is >> word;)
	{
		if (isSign(word[0])) {
			sign = word[0];
		}
		else {
			Monom monom;
			monom.initWithString(word, sign);
			polynom.push(monom);
		}		
	}
}

string Polynom::toString()
{
	string res = "";
	auto headInput = polynom.pFirst;
	auto currNodeInput = polynom.pFirst->next;	
	while (currNodeInput->next != headInput) {
		if (currNodeInput->data.coef > 0)
			res += "+";
		if (currNodeInput->data.coef != 1 && currNodeInput->data.coef != -1)
			res = res + to_string(currNodeInput->data.coef);
		int*  degs = currNodeInput->data.getDegreeArray();
		for (int i = 0; i < 3; i++)
		{
			if (degs[i] != 0)
				switch (i)
				{
				case 0:
					res += "x^";
					res += to_string(degs[i]);
					break;
				case 1:
					res += "y^";
					res += to_string(degs[i]);
					break;
				case 2:
					res += "z^";
					res += to_string(degs[i]);
					break;
				default:
					break;
				}
		}
		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		if (currNodeInput->data.coef > 0)
			res += "+";
		if(currNodeInput->data.coef != 1 && currNodeInput->data.coef != -1)
			res = res + to_string(currNodeInput->data.coef);
		int*  degs = currNodeInput->data.getDegreeArray();
		for (int i = 0; i < 3; i++)
		{
			if (degs[i] != 0)
				switch (i)
				{
				case 0:
					res += "x^";
					res += to_string(degs[i]);
					break;
				case 1:
					res += "y^";
					res += to_string(degs[i]);
					break;
				case 2:
					res += "z^";
					res += to_string(degs[i]);
					break;
				default:
					break;
				}
		}
	}
	return res;
}

Polynom & Polynom::operator+=(const Polynom & poly)
{
    auto headInput = poly.polynom.pFirst;
	auto currNodeInput = poly.polynom.pFirst->next;
	auto start = polynom.pFirst;
	while (currNodeInput->next != headInput) {
		start = polynom.push_after(currNodeInput->data, start);
		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		start = polynom.push_after(currNodeInput->data, start);
	}
	polyString = toString();
	return *this;
}

Polynom& Polynom::operator=(const Polynom &poly)
{
	polynom.clear();
	auto start = polynom.pFirst;
	auto headInput = poly.polynom.pFirst;
	auto currNodeInput = poly.polynom.pFirst->next;
	while (currNodeInput->next != headInput) {
		start = polynom.push_after(currNodeInput->data, start);
		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		polynom.push_after(currNodeInput->data, start);
	}
	polyString = toString();
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& poly)
{
	*this += -poly;
	return *this;
}

Polynom & Polynom::operator*=(const Polynom & poly)
{
	vector<Polynom> polynomas;
	auto headInput = poly.polynom.pFirst;
	auto currNodeInput = poly.polynom.pFirst->next;
	while (currNodeInput->next != headInput) {

		Polynom pol(*this);

		auto headThis = pol.polynom.pFirst;
		auto currNodeThis = pol.polynom.pFirst->next;
		while (currNodeThis->next != headThis) {
			currNodeThis->data *= currNodeInput->data;
			currNodeThis = currNodeThis->next;
		}
		if (currNodeThis != headThis) {
			currNodeThis->data *= currNodeInput->data;
		}

		polynomas.push_back(pol);

		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		Polynom pol(*this);

		auto headThis = pol.polynom.pFirst;
		auto currNodeThis = pol.polynom.pFirst->next;
		while (currNodeThis->next != headThis) {
			currNodeThis->data *= currNodeInput->data;
			currNodeThis = currNodeThis->next;
		}
		if (currNodeThis != headThis) {
			currNodeThis->data *= currNodeInput->data;
		}

		polynomas.push_back(pol);
	}
	
	int i = polynomas.size();
	while (i != 1) {
		i--;
		polynomas.front() += polynomas.back();
		polynomas.pop_back();
	}

	*this = polynomas.front();

	polyString = toString();

	return *this;
}

void Polynom::derivativeBy(char c)
{
	auto headInput = polynom.pFirst;
	auto currNodeInput = polynom.pFirst->next;
	while (currNodeInput != headInput) {
		currNodeInput->data.derivate(c);		
		currNodeInput = currNodeInput->next;
	}

	headInput = polynom.pFirst;
	currNodeInput = polynom.pFirst;
	while (currNodeInput->next != headInput) {
		if (currNodeInput->next->data.coef == 0) {
			auto ref = currNodeInput->next;						
			if (currNodeInput->next->next->next == headInput) {
				if (currNodeInput->next->next->data.coef == 0) {
					auto ref2 = currNodeInput->next->next;
					currNodeInput->next = currNodeInput->next->next->next;
					delete ref2;					
				}
			}
			else
			{
				currNodeInput->next = currNodeInput->next->next;
			}
			delete ref;

		}
		currNodeInput = currNodeInput->next;
	}
	
	polyString = toString();

}


Polynom Polynom::operator-() const
{
	auto poly = *this;

	auto headInput = poly.polynom.pFirst;
	auto currNodeInput = poly.polynom.pFirst->next;
	while (currNodeInput->next != headInput) {
		currNodeInput->data.coef *= -1;
		currNodeInput = currNodeInput->next;
	}
	if (currNodeInput != headInput) {
		currNodeInput->data.coef *= -1;
	}
	poly.polyString = poly.toString();

	return poly;
}



ostream & operator<<(ostream & os, Polynom &poly)
{
	os << poly.toString();
	return os;
}
