#pragma once
#include <string>
#include <cmath>
#include <regex>
#include <sstream>
#include <iostream>
using namespace std;

const int MAX_DEGREE = 10;

class Monom {
	string input;

	bool parseStringToDegree() {
		smatch m, dg, cf;

		bool firstVariable;

		regex xMask("(x\\^*\\d*)");
		regex yMask("(y\\^*\\d*)");
		regex zMask("(z\\^*\\d*)");


		auto getCoef = [&firstVariable, this](){
			if (firstVariable)
			{
				firstVariable = false;
				int i = 0;
				while (input[i++] < 119)
				{

				}
				coef = stoi(input.substr(0,i));
			}
		};

		auto getDeg = [](string str, int &deg) {
			if (str[1] != '^') {
				str.erase(0, 1);
			}
			else {
				str.erase(0, 2);
			}
			deg = stoi(str);
		};

		int degs[3] = { 0 };

		//Можно реализовать для неопределенного числа переменных

		if (regex_search(input, m, xMask)) 
		{
			getCoef();
			getDeg(m.str(), degs[0]);

		}
		if (regex_search(input, m, yMask))
		{
			getCoef();
			getDeg(m.str(), degs[1]);
		}
		
		if (regex_search(input, m, zMask)) 
		{
			getCoef();
			getDeg(m.str(), degs[2]);
		}
		
		degree = createDegree(degs);
		
		if (degree == 0) {
			coef = stoi(input);
		}

		return true;
	}

	int createDegree(int * degs) {
		return pow(MAX_DEGREE, 2) * degs[0] + pow(MAX_DEGREE, 1) * degs[1] +  degs[2];
	}

public:
	long long int degree;
	int coef;

	Monom(int degree = 0) {
		this->degree = degree;
		coef = 0;
	};

	Monom(Monom &mony) {
		degree = mony.degree;
		coef = mony.coef;
		input = mony.input;
	};

	bool initWithString(string str, char sign) {
		input = str;
		parseStringToDegree();
		if (sign == '-') {
			coef *= -1;
		}
		return true;
	}


	int* getDegreeArray() {
		auto deg = degree;
		int* degs = new int [3];
		
		auto power = [](int k, int pow){
			int res = 1;
			for (int i = 0; i < pow; i++)
			{
				res *= k;
			}
			return res;
		};
		
		for (int i = 0; i < 3; i++)
		{
			degs[i] = deg / power(MAX_DEGREE, 2 - i) ;
			deg %= power(MAX_DEGREE, 2 - i);
		}
		return degs;
	}

	void derivate(char c) {
		int *degs = getDegreeArray();
		int i;
		switch (c)
		{
		case 'x':
			i = 0;
			break;
		case 'y':
			i = 1;
			break;
		case 'z':
			i = 2;
			break;
		default:
			throw 0;
		}
		
		if (degs[i] > 0)
			coef *= degs[i]--;
		else
			coef = 0;
		degree = createDegree(degs);
	}

	bool operator==(Monom& mon) {
		return degree == mon.degree;
	}

	bool operator!=(Monom& mon) {
		return degree != mon.degree;
	}

	bool operator>(Monom& mon) {
		return degree > mon.degree;
	}

	bool operator<(Monom& mon) {
		return degree < mon.degree;
	}

	Monom& operator-=(Monom& mon) {
		coef += mon.coef;
		return *this;
	}

	Monom& operator+=(Monom& mon) {
		coef -= mon.coef;
		return *this;
	}
	Monom& operator*=(Monom& mon) {
		int *degs1 = getDegreeArray();
		int *degs2 = mon.getDegreeArray();
		for (int i = 0; i < 3; i++)
		{
			degs1[i] += degs2[i];
		}
		degree = createDegree(degs1);
		coef *= mon.coef;
		return *this;
	}




};
