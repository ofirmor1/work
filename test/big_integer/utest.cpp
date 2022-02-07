#include "mu_test.h"
#include "big_integer.hpp"

#include <iostream>

using namespace std;

BEGIN_TEST(size_zero_when_ctr_called)
    BigInteger bi;
	ASSERT_EQUAL(0, bi.getSize());

END_TEST


BEGIN_TEST(passing_positive_BigInteger_as_argument_to_ctr)
	string s = "123456";
	BigInteger b1("123456");
	BigInteger b2(b1);
	ASSERT_EQUAL(s, b2.toString());
	ASSERT_EQUAL(6, b2.getSize());

END_TEST

BEGIN_TEST(passing_negative_BigInteger_as_argument_to_ctr)
	string s = "-123456";
	BigInteger b1("-123456");
	BigInteger b2(b1);
	ASSERT_EQUAL(s, b2.toString());
	ASSERT_EQUAL(6, b2.getSize());

END_TEST


BEGIN_TEST(not_equal_BI_return_minus_one_when_b1_neg_b2_pos)
	BigInteger b1(-25L);
	BigInteger b2(25L);
	ASSERT_EQUAL(-1,b1.equals(b2));

END_TEST


BEGIN_TEST(not_equal_BI_return_minus_one_when_b1_less_than_b2)
	BigInteger b1(200L);
	BigInteger b2(201L);
	ASSERT_EQUAL(-1,b1.equals(b2));

END_TEST


BEGIN_TEST(equals_return_one_when_b1_greater_than_b2)
	BigInteger b1(14L);
	BigInteger b2(13L);
	ASSERT_EQUAL(1,b1.equals(b2));

END_TEST


BEGIN_TEST(equals_return_one_when_b1_pos_b2_neg)
	BigInteger b1(2L);
	BigInteger b2(-2L);
	ASSERT_EQUAL(1,b1.equals(b2));

END_TEST



BEGIN_TEST(equals_check_two_negatives_return_one_when_b1_greater_than_b2)
	BigInteger b1(-10L);
	BigInteger b2(-12L);
	ASSERT_EQUAL(1,b1.equals(b2));

END_TEST


//Comparison - Greater Than
BEGIN_TEST(comparison_greater_than_true_when_b1_and_b2_negative_but_b1_greater)
	BigInteger b1(-122);
	BigInteger b2(-123);
	ASSERT_THAT(greaterthan(b1, b2));

END_TEST


BEGIN_TEST(comparison_greater_than_true_when_b1_and_b2_positive_but_b1_greater)
	BigInteger b1(122);
	BigInteger b2(123);
	ASSERT_THAT(greaterthan(b1, b2));

END_TEST


BEGIN_TEST(comparison_greater_than_true_when_b1_and_b2_positive_b1_1000_b2_10)
	BigInteger b1(10);
	BigInteger b2(1000);
	if(!(greaterthan(b1, b2)))
    {
        ASSERT_FAIL("b2(1000) is greater than b1(10)");
    }

END_TEST


//Comparison - Equal to Greater Than
BEGIN_TEST(comparison_greater_or_equal_true_when_b1_and_b2_negative_but_equal)
	BigInteger b1(-123);
	BigInteger b2(-123);
	ASSERT_THAT(greaterOrEqual(b1, b2));

END_TEST


BEGIN_TEST(comparison_greater_or_equal_true_when_b1_and_b2_negative_but_b1_greater)
	BigInteger b1(-122);
	BigInteger b2(-123);
	ASSERT_THAT(greaterOrEqual(b1, b2));

END_TEST


BEGIN_TEST(comparison_greater_or_equal_true_when_b1_and_b2_positive_but_b1_greater)
	BigInteger b1(123);
	BigInteger b2(122);
	ASSERT_THAT(greaterOrEqual(b1, b2));

END_TEST


BEGIN_TEST(comparison_greater_or_equal_true_when_b1_and_b2_positive_b1_1000_b2_10)
	BigInteger b1(10);
	BigInteger b2(1000);
	if(!(greaterOrEqual(b1, b2)))
	{
		ASSERT_FAIL("b2(1000) is greater than b1(10)");
	}

END_TEST
//Comparison - Less Than
BEGIN_TEST(comparison_less_or_equal_true_when_b1_and_b2_negative_but_b2_greater)
	BigInteger b1(-123);
	BigInteger b2(-122);
	ASSERT_THAT(lessthan(b1, b2));

END_TEST


BEGIN_TEST(comparison_less_or_equal_true_when_b1_and_b2_positive_but_b2_greater)
	BigInteger b1(122);
	BigInteger b2(123);
	ASSERT_THAT(lessthan(b1, b2));

END_TEST


BEGIN_TEST(comparison_less_or_equal_true_when_b1_and_b2_positive_b1_1000_b2_10)
	BigInteger b1(1000);
	BigInteger b2(10);
	if(!(lessthan(b1, b2)))
	{
		ASSERT_FAIL("b2(10) is less than b1(1000)");
	}

END_TEST

BEGIN_TEST(string_test)
    string str = "123";
    BigInteger num(str);
    string p = num.toString();
    printf("%s ", p.c_str());
    cout << p << endl;
    int n = p.length();
    ASSERT_EQUAL(n, str.length());
     
END_TEST


BEGIN_TEST(add_sub_test)
    BigInteger a(123L);
    BigInteger b(12L);
    BigInteger c(0L);
    BigInteger d(-24L);
    ASSERT_EQUAL(a.getSize(), 3);
    ASSERT_EQUAL(b.getSize(), 2);
    c = a.add(b);
    string res = c.toString();
    cout << res.c_str() << endl;
    printf("%s ", res.c_str());
    ASSERT_EQUAL(c.getSize(), 3);
    c = a.add(d);
    ASSERT_EQUAL(c.getSize(), 2);
    // ASSERT_EQUAL(az, 135);
    // cout << a.toString() << endl;

    // ASSERT_PASS();
END_TEST


BEGIN_SUITE(single_linked_list_tests)
    TEST(size_zero_when_ctr_called)
    TEST(passing_positive_BigInteger_as_argument_to_ctr)
    TEST(passing_negative_BigInteger_as_argument_to_ctr)
    TEST(not_equal_BI_return_minus_one_when_b1_neg_b2_pos)
    TEST(not_equal_BI_return_minus_one_when_b1_less_than_b2)
    TEST(equals_return_one_when_b1_greater_than_b2)
    TEST(equals_return_one_when_b1_pos_b2_neg)
    TEST(equals_check_two_negatives_return_one_when_b1_greater_than_b2)
    TEST(comparison_greater_than_true_when_b1_and_b2_positive_but_b1_greater)
    TEST(comparison_greater_than_true_when_b1_and_b2_positive_b1_1000_b2_10)
    TEST(comparison_greater_or_equal_true_when_b1_and_b2_negative_but_equal)
    TEST(comparison_greater_or_equal_true_when_b1_and_b2_negative_but_b1_greater)
    TEST(comparison_greater_or_equal_true_when_b1_and_b2_positive_but_b1_greater)
    TEST(comparison_greater_or_equal_true_when_b1_and_b2_positive_b1_1000_b2_10)
    TEST(comparison_less_or_equal_true_when_b1_and_b2_negative_but_b2_greater)
    TEST(comparison_less_or_equal_true_when_b1_and_b2_positive_but_b2_greater)
    TEST(comparison_less_or_equal_true_when_b1_and_b2_positive_b1_1000_b2_10)
    TEST(string_test)
    TEST(add_sub_test)

END_SUITE