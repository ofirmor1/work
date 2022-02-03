#include "mu_test.h"
#include "big_integer.hpp"

#include <iostream>

using namespace std;

BEGIN_TEST(string_test)
    string str = "123";
    BigInteger num(str);
    string p = num.toString();
    cout << p << endl;
    int n = p.length();
    ASSERT_EQUAL(n, sizeof(str) - 1);
    // ASSERT_PASS();
        
END_TEST


BEGIN_SUITE(single_linked_list_tests)
    TEST(string_test)

END_SUITE