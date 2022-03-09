#include "mu_test.h"
#include "mystring.hpp"
#include "store.hpp"

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

BEGIN_TEST(store_tests)
static const size_t SIZE = 64;
    Store arr(SIZE);
    ASSERT_EQUAL(arr.getCapacity(), 64);
    ASSERT_EQUAL(arr.getSize(), 0);

    ASSERT_EQUAL(arr[2], 0);
    arr.set(2, 2);
    ASSERT_EQUAL(arr[2], 2);

    arr.reset(3);
    for (size_t i = 0; i < arr.getSize(); i++)
    {
        ASSERT_EQUAL(arr[i], 3);
    }

END_TEST  

BEGIN_SUITE(exam_tests)
    TEST(string_tests)
    TEST(store_tests)
END_SUITE