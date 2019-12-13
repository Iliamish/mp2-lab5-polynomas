#include <gtest.h>
#include "Polynom.h"

TEST(Monom, can_create_monom)
{

	ASSERT_NO_THROW(Monom mony);
};

TEST(Monom, can_create_first_monom)
{
	Monom mony(-1);
	EXPECT_EQ(mony.degree, -1);
}

TEST(Monom, can_create_monom_with_string_1)
{
	string str = "2x2y^2z^2";
	Monom mony;
	mony.initWithString(str, '+');
	
	EXPECT_EQ(mony.coef, 2);
}

TEST(Monom, can_create_monom_with_string_2)
{
	string str = "2x2y^2z^2";
	Monom mony;
	mony.initWithString(str, '-');

	EXPECT_EQ(mony.coef, -2);
}

TEST(Monom, can_create_monom_with_string_3)
{
	string str = "2x2y^2z^2";
	Monom mony;
	mony.initWithString(str, '+');

	EXPECT_EQ(mony.degree, 222);
}

TEST(Monom, can_create_monom_with_string_7)
{
	string str = "2x2y^2z^2";
	Monom mony;
	mony.initWithString(str, '+');

	EXPECT_EQ(mony.degree, 222);
}

TEST(Monom, can_create_monom_with_string_4)
{
	string str = "2y^2z^2";
	Monom mony;
	mony.initWithString(str, '+');

	EXPECT_EQ(mony.degree, 22);
}

TEST(Monom, can_create_monom_with_string_5)
{
	string str = "2z^2";
	Monom mony;
	mony.initWithString(str, '+');

	EXPECT_EQ(mony.degree, 2);
}

TEST(Monom, can_create_monom_with_string_6)
{
	string str = "2";
	Monom mony;
	mony.initWithString(str, '+');

	EXPECT_EQ(mony.degree, 0);
}

TEST(Monom, can_add_monom)
{
	string str = "2x2y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	mony1 += mony2;

	EXPECT_EQ(mony1.coef, 7);
}

TEST(Monom, can_sub_monom)
{
	string str = "2x2y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	mony1 -= mony2;

	EXPECT_EQ(mony1.coef, -3);
}

TEST(Monom, can_mul_monom_1)
{
	string str = "2x2y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	mony1 *= mony2;

	EXPECT_EQ(mony1.coef, 10);
}

TEST(Monom, can_mul_monom_2)
{
	string str = "2x2y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	mony1 *= mony2;

	EXPECT_EQ(mony1.degree, 444);
}

TEST(Monom, less_monom)
{
	string str = "2x1y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	EXPECT_EQ(mony1 < mony2, 1);
}

TEST(Monom, great_monom)
{
	string str = "2x3y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	EXPECT_EQ(mony1 > mony2, 1);
}


TEST(Monom, equal_monom)
{
	string str = "2x2y^2z^2";
	Monom mony1;
	mony1.initWithString(str, '+');

	str = "5x2y^2z^2";
	Monom mony2;
	mony2.initWithString(str, '+');

	EXPECT_EQ(mony1 == mony2, 1);
}

TEST(Polynom, can_create_polynom)
{
	Polynom poly("x^1y^1z^1 + x2 + z2");
	EXPECT_EQ(poly.toString(), "+z^2+x^1y^1z^1+x^2");
}


TEST(Polynom, can_add_polynom)
{
	string str = "2x^2y^2z^2 + 3";
	string str2 = "2x^2y^2z^2 + 6";
	Polynom poly(str);

	Polynom poly2(str2);

	poly += poly2;

	EXPECT_EQ(poly.toString(), "+9+4x^2y^2z^2");
}

TEST(Polynom, can_sub_polynom_1)
{
	string str = "2x^2y^2z^2 + 3";
	string str2 = "2x^2y^2z^2 + 6";
	Polynom poly(str);

	Polynom poly2(str2);

	poly -= poly2;

	EXPECT_EQ(poly.toString(), "-3");
}

TEST(Polynom, can_sub_polynom_2)
{
	string str = "3x^2y^2z^2 + 3";
	string str2 = "2x^2y^2z^2 + 6";
	Polynom poly(str);

	Polynom poly2(str2);

	poly -= poly2;

	EXPECT_EQ(poly.toString(), "-3+x^2y^2z^2");
}

TEST(Polynom, can_mul_poly_1)
{
	string str = "3y^2z^2";
	string str2 = "2x^2y^2z^2";
	Polynom poly(str);

	Polynom poly2(str2);

	poly *= poly2;

	EXPECT_EQ(poly.toString(), "+6x^2y^4z^4");
}

TEST(Polynom, can_mul_poly_2)
{
	string str = "3";
	string str2 = "2x^2y^2z^2";
	Polynom poly(str);

	Polynom poly2(str2);

	poly *= poly2;

	EXPECT_EQ(poly.toString(), "+6x^2y^2z^2");
}

TEST(Polynom, can_mul_poly_3)
{
	string str = "z^2 + x^2";
	string str2 = "2x^2y^2z^2";
	Polynom poly(str);

	Polynom poly2(str2);

	poly *= poly2;

	EXPECT_EQ(poly.toString(), "+2x^2y^2z^4+2x^4y^2z^2");
}

TEST(Polynom, can_derivate_monom)
{

	string str = "2x^2y^2z^2";
	Polynom poly(str);

	poly.derivativeBy('x');

	EXPECT_EQ(poly.toString(), "+4x^1y^2z^2");
}
