#include "Polynom.h"

int main() {
	string str = "2x^2y^2z^2 - 2x^2y^2z^3 ";
	string str2 = "2x^2y^2z^2 + 2x^2y^2z^4 ";
	Polynom poly(str);

	Polynom poly2(str2);

	poly *= poly2;

	poly.derivativeBy('x');

	cout << poly;

	system("pause");
	
	return 0;
}