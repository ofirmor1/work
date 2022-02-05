#include "mu_test.h"
#include "big_integer.hpp"

#include <iostream>

using namespace std;

BEGIN_TEST(string_test)
    string str = "123";
    BigInteger num(str);
    string p = num.toString();
    printf("%s ", p.c_str());
    cout << p << endl;
    int n = p.length();
    ASSERT_EQUAL(n, str.length());
        
END_TEST


BEGIN_TEST(passing_positive_string_to_constructor)
    string str = "123";
    BigInteger a(str);
    string res = a.toString();
    cout << res << endl;
    ASSERT_EQUAL(res, str);

END_TEST

BEGIN_TEST(add_test)
    BigInteger a(123);
    BigInteger b(12);
    BigInteger c;
    BigInteger d(-24);
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
    TEST(passing_positive_string_to_constructor)
    TEST(string_test)
    TEST(add_test)

END_SUITE