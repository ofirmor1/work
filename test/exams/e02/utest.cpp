#include "mu_test.h"
#include "mystring.hpp"

#include <string>
#include <iostream>
#include <cassert>
#include <stddef.h>

using namespace cpp;

BEGIN_TEST(string_tests)
using namespace std;
    string s1 = "Hello";
    string s2 = "lloHe";
    bool res = isReversed(s1, s2);
    ASSERT_EQUAL(res, true);

    s1 = "abcde";
    s2 = "bcdae";
    res = isReversed(s1, s2);
    ASSERT_EQUAL(res, false);

    s1 = "abcde";
    s2 = "bcdaefg";
    res = isReversed(s1, s2);
    ASSERT_EQUAL(res, false);



END_TEST   



BEGIN_SUITE(exam_tests)
    TEST(string_tests)
END_SUITE