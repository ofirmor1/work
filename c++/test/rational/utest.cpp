#include "mu_test.h"
#include "rational.hpp"

#include <iostream>

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

    ASSERT_EQUAL(r.getNumerator(), 1);
    ASSERT_EQUAL(r.getDenominator(), -2);

    r = Rational(7, -32);

    ASSERT_EQUAL(r.getNumerator(), 7);
    ASSERT_EQUAL(r.getDenominator(), -32);

END_TEST

BEGIN_TEST(copy_test)
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

END_TEST

BEGIN_TEST(operator_minus_two_rational)
    Rational a(3, 4);
    Rational b(6, 8);
    Rational res;

    // res = a - b;
    // res.operator=(a.operator-() b);
    ASSERT_PASS();

END_TEST

BEGIN_TEST(operator_pre_increment_two_rational)
    Rational a(12, 25);
    Rational b(2, 6);

    a = ++b;

    Rational c(1,3);
    ASSERT_EQUAL(a.getNumerator(), a.getNumerator());
    ASSERT_EQUAL(a.getDenominator(), a.getDenominator());

    ASSERT_EQUAL(a.getNumerator(), 4);
    ASSERT_EQUAL(a.getDenominator(), 3);

    ASSERT_EQUAL(b.getNumerator(), 4);
    ASSERT_EQUAL(b.getDenominator(), 3);

END_TEST



BEGIN_TEST(operator_post_increment_two_rational)
    Rational a(12, 25);
    Rational b(2, 6);

    a = b++;

    Rational c(1,3);
    ASSERT_EQUAL(a.getNumerator(), a.getNumerator());
    ASSERT_EQUAL(a.getDenominator(), a.getDenominator());

    ASSERT_EQUAL(a.getNumerator(), 1);
    ASSERT_EQUAL(a.getDenominator(), 3);

    ASSERT_EQUAL(b.getNumerator(), 4);
    ASSERT_EQUAL(b.getDenominator(), 3);

END_TEST

BEGIN_TEST(operator_post_decrement_two_rational)
    Rational a(12, 25);
    Rational b(7, 6);

    a = b--;

    Rational c(1,3);
    ASSERT_EQUAL(a.getNumerator(), a.getNumerator());
    ASSERT_EQUAL(a.getDenominator(), a.getDenominator());

    ASSERT_EQUAL(a.getNumerator(), 7);
    ASSERT_EQUAL(a.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);

END_TEST



BEGIN_TEST(operator_pre_decrement_two_rational)
    Rational a(12, 25);
    Rational b(7, 6);

    a = --b;

    Rational c(1,3);
    ASSERT_EQUAL(a.getNumerator(), a.getNumerator());
    ASSERT_EQUAL(a.getDenominator(), a.getDenominator());

    ASSERT_EQUAL(a.getNumerator(), 1);
    ASSERT_EQUAL(a.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);

END_TEST


BEGIN_TEST(addition_two_positive)
    Rational a(1, 3);
    Rational b(2, 4); 
    Rational c; 

    c = a + b; // 1/3 + 1/2 = 5/6

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b += a; 

    ASSERT_EQUAL(c.getNumerator(), 5);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 5);
    ASSERT_EQUAL(b.getDenominator(), 6);
    
END_TEST


BEGIN_TEST(addition_two_negative)
    Rational a(-1, 3);
    Rational b(-2, 4); 
    Rational c; 

    c = a + b; // -1/3 -1/2 = -5/6

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b += a; 

    ASSERT_EQUAL(c.getNumerator(), -5);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), -5);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(addition_positive_and_negative)
    Rational a(-1, 3);
    Rational b(2, 4); 
    Rational c; 

    c = a + b; // 1/2 - 1/3 = 1/6

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b += a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(addition_positive_with_zero)
    Rational a(1, 3);
    Rational b(0, 2); 
    Rational c; 

    c = a + b; // 0 + 1/3 = 1/3

    ASSERT_EQUAL(b.getNumerator(), 0);
    ASSERT_EQUAL(b.getDenominator(), 1);
    b += a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 3);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 3);
END_TEST


BEGIN_TEST(addition_negative_with_zero)
    Rational a(-1, 3);
    Rational b(0, 2); 
    Rational c; 

    c = a + b; // 0 - 1/3 = -1/3

    ASSERT_EQUAL(b.getNumerator(), 0);
    ASSERT_EQUAL(b.getDenominator(), 1);
    b += a; 

    ASSERT_EQUAL(c.getNumerator(), -1);
    ASSERT_EQUAL(c.getDenominator(), 3);

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 3);
END_TEST


BEGIN_TEST(subtraction_two_positive)
    Rational a(1, 3);
    Rational b(1, 2); 
    Rational c; 

    c = b - a; // 1/2 - 1/3 = 1/6

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b -= a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(subtraction_two_negative)
    Rational a(-1, 3);
    Rational b(-1, 2); 
    Rational c; 

    c = b - a; // -1/2 - (-1/3) = -1/6

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b -= a; 

    ASSERT_EQUAL(c.getNumerator(), -1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(subtraction_positive_and_negative)
    Rational a(-1, 3);
    Rational b(1, 2); 
    Rational c; 

    c = b - a; // 1/2 - (-1/3) = 5/6

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b -= a; 

    ASSERT_EQUAL(c.getNumerator(), 5);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 5);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(subtraction_positive_with_zero)
    Rational a(0, 3);
    Rational b(1, 2); 
    Rational c; 

    c = b - a; // 1/2 - 0 = 1/2

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b -= a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 2);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
END_TEST


BEGIN_TEST(subtraction_negative_with_zero)
    Rational a(0, 3);
    Rational b(-1, 2); 
    Rational c; 

    c = b - a; // -1/2 - 0 = -1/2

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b -= a; 

    ASSERT_EQUAL(c.getNumerator(), -1);
    ASSERT_EQUAL(c.getDenominator(), 2);

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
END_TEST


BEGIN_TEST(mul_two_positive)
    Rational a(1, 3);
    Rational b(1, 2); 
    Rational c; 

    c = b * a; // 1/2 * 1/3 = 1/6

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b *= a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(mul_two_negative)
    Rational a(-1, 3);
    Rational b(-1, 2); 
    Rational c; 

    c = b * a; // -1/2 * -1/3 = 1/6

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b *= a; 

    ASSERT_EQUAL(c.getNumerator(), 1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), 1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(mul_positive_and_negative)
    Rational a(1, 3);
    Rational b(-1, 2); 
    Rational c; 

    c = b * a; // -1/2 * 1/3 = -1/6

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 2);
    b *= a; 

    ASSERT_EQUAL(c.getNumerator(), -1);
    ASSERT_EQUAL(c.getDenominator(), 6);

    ASSERT_EQUAL(b.getNumerator(), -1);
    ASSERT_EQUAL(b.getDenominator(), 6);
END_TEST


BEGIN_TEST(mul_positive_with_zero)
    Rational a(1, 3);
    Rational b(0, 2); 
    Rational c; 

    c = b * a; // 0 * 1/3 = 0
    c.print(std::cout);

    ASSERT_EQUAL(b.getNumerator(), 0);
    ASSERT_EQUAL(b.getDenominator(), 1);
    b *= a; 

    ASSERT_EQUAL(c.getNumerator(), 0);
    ASSERT_EQUAL(c.getDenominator(), 3);

    ASSERT_EQUAL(b.getNumerator(), 0);
    ASSERT_EQUAL(b.getDenominator(), 3);
END_TEST


// BEGIN_TEST(mul_negative_with_zero)

// END_TEST


// BEGIN_TEST(div_two_positive)

// END_TEST


// BEGIN_TEST(div_two_negative)

// END_TEST


// BEGIN_TEST(div_positive_and_negative)

// END_TEST


// BEGIN_TEST(div_positive_with_zero)

// END_TEST


// BEGIN_TEST(div_negative_with_zero)

// END_TEST


// // comparison tests
// BEGIN_TEST(test_two_positive_equal)

// END_TEST


// BEGIN_TEST(test_two_negative_equal)

// END_TEST


// BEGIN_TEST(test_two_positive_not_equal)

// END_TEST


// BEGIN_TEST(test_two_negative_not_equal)

// END_TEST


// BEGIN_TEST(one_greater_than_zero)

// END_TEST


// BEGIN_TEST(one_houndred_greater_than_one)

// END_TEST


// BEGIN_TEST(minus_one_greater_than_minus_two)

// END_TEST


// BEGIN_TEST(minus_one_greater_than_minus_one_houndred)

// END_TEST


// BEGIN_TEST(one_greater_than_minus_one)

// END_TEST


// BEGIN_TEST(zero_less_than_one)

// END_TEST


// BEGIN_TEST(one_less_than_one_houndred)

// END_TEST


// BEGIN_TEST(minus_two_less_than_minus_one)

// END_TEST


// BEGIN_TEST(minus_one_houndred_less_than_minus_one)

// END_TEST


// BEGIN_TEST(minus_one_less_than_one)

// END_TEST


// BEGIN_TEST(one_greaterOrEqual_than_zero)

// END_TEST


// BEGIN_TEST(one_greaterOrEqual_than_one)

// END_TEST


// BEGIN_TEST(minus_one_greaterOrEqual_than_minus_two)

// END_TEST


// BEGIN_TEST(zero_lessOrEqual_than_one)

// END_TEST

// BEGIN_TEST(zero_lessOrEqual_than_zero)

// END_TEST


// BEGIN_TEST(minus_two_lessOrEqual_than_minus_one)

// END_TEST

BEGIN_SUITE(rational_tests)
    TEST(create_a_zero_test)
    TEST(create_infinity_test)
    TEST(add_test_positive_rational)
    TEST(add_test_negative_rational)
    TEST(copy_test)
    //operators tests;
    TEST(operator_minus_two_rational)
    TEST(operator_pre_increment_two_rational)
    TEST(operator_post_increment_two_rational)
    TEST(operator_post_decrement_two_rational)
    TEST(operator_pre_decrement_two_rational)
    TEST(addition_two_positive)
    TEST(addition_two_negative)
    TEST(addition_positive_and_negative)
    TEST(addition_positive_with_zero)
    TEST(addition_negative_with_zero)
    TEST(subtraction_two_positive)
    TEST(subtraction_two_negative)
    TEST(subtraction_positive_and_negative)
    TEST(subtraction_positive_with_zero)
    TEST(subtraction_negative_with_zero)
    TEST(mul_two_positive)
    TEST(mul_two_negative)
    TEST(mul_positive_and_negative)
    TEST(mul_positive_with_zero)
    // TEST(mul_negative_with_zero)
    // TEST(div_two_positive)
    // TEST(div_two_negative)
    // TEST(div_positive_and_negative)
    // TEST(div_positive_with_zero)
    // TEST(div_negative_with_zero)
    // //comparison tests
    // TEST(test_two_positive_equal)
    // TEST(test_two_negative_equal)
    // TEST(test_two_positive_not_equal)
    // TEST(test_two_negative_not_equal)
    // TEST(one_greater_than_zero)
    // TEST(one_houndred_greater_than_one)
    // TEST(minus_one_greater_than_minus_two)
    // TEST(minus_one_greater_than_minus_one_houndred)
    // TEST(one_greater_than_minus_one)
    // TEST(zero_less_than_one)
    // TEST(one_less_than_one_houndred)
    // TEST(minus_two_less_than_minus_one)
    // TEST(minus_one_houndred_less_than_minus_one)
    // TEST(minus_one_less_than_one)
    // TEST(one_greaterOrEqual_than_zero)
    // TEST(one_greaterOrEqual_than_one)
    // TEST(minus_one_greaterOrEqual_than_minus_two)
    // TEST(zero_lessOrEqual_than_one)
    // TEST(zero_lessOrEqual_than_zero)
    // TEST(minus_two_lessOrEqual_than_minus_one)

END_SUITE