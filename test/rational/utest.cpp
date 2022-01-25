#include "mu_test.h"
#include "Rational.hpp"

BEGIN_TEST(add_test_positive_rational)
	Rational r(1, 2);

        ASSERT_EQUAL(r.getNumerator(), 1);
        ASSERT_EQUAL(r.getDenominator(), 2);

        r = Rational(5,10);

        ASSERT_EQUAL(r.getNumerator(), 1);
        ASSERT_EQUAL(r.getDenominator(), 2);

        r = Rational(7,32);

        ASSERT_EQUAL(r.getNumerator(), 7);
        ASSERT_EQUAL(r.getDenominator(), 32);

        r = Rational(-7, -32);
        ASSERT_EQUAL(r.getNumerator(), 7);
        ASSERT_EQUAL(r.getDenominator(), 32);
END_TEST

BEGIN_TEST(create_a_zero_test)
	Rational r(0, 2);
        ASSERT_EQUAL(r.getNumerator(), 0);
        ASSERT_EQUAL(r.getDenominator(), 1);

        r = Rational(0, 12);
        ASSERT_EQUAL(r.getNumerator(), 0);
        ASSERT_EQUAL(r.getDenominator(), 1);
END_TEST


BEGIN_TEST(create_infinity_test)
	Rational r(1, 0);
        ASSERT_FAIL("can't divide by zero");
END_TEST

BEGIN_TEST(add_test_negative_rational)
	Rational r = Rational(-1,2);

        ASSERT_EQUAL(r.getNumerator(), -1);
        ASSERT_EQUAL(r.getDenominator(), 2);

        r = Rational(5, -10);

        ASSERT_EQUAL(r.getNumerator(), -1);
        ASSERT_EQUAL(r.getDenominator(), 2);

        r = Rational(7, -32);

        ASSERT_EQUAL(r.getNumerator(), -7);
        ASSERT_EQUAL(r.getDenominator(), 32);
END_TEST

BEGIN_TEST(x)
        Rational b; 
        Rational zero;    // == one(0, 1)
        Rational one(1);  // == one(1, 1)
        Rational w(2);    // == one(2, 1)

        Rational q(3, 4);
        Rational qcopy = q;
        Rational s(8, 24); // == 1/3
        Rational t(8, 24, false); // == 8/24

        q.mul(one);
        Rational q34(3, 4);
        qcopy.mul(zero);
        Rational q0(0, 4);

        ASSERT_THAT(q34.equal(q));
        ASSERT_THAT(q0.equal(qcopy));
END_TEST

BEGIN_SUITE(不耻下问 this is a description)
    TEST(create_a_zero_test)
    TEST(create_infinity_test)
    TEST(add_test_positive_rational)
    TEST(add_test_negative_rational)
    TEST(x)
END_SUITE