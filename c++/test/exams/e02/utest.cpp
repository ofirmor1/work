#include "mu_test.h"
#include "mystring.hpp"
#include "store.hpp"
#include "vector.hpp"
#include "matrix.hpp"

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
    for (size_t i = 0; i < arr.getSize(); ++i)
    {
        ASSERT_EQUAL(arr[i], 3);
    }

END_TEST  

BEGIN_TEST(vector_tests)
    Vector vec;

    for (size_t i = 1; i < 10; ++i)
    {
        vec.insert(i);
    }
    
    ASSERT_EQUAL(vec.sumElements(0, 9), 45);

    vec.Update(2, 10);
    ASSERT_EQUAL(vec[2], 10);

END_TEST

// BEGIN_TEST(matrix_tests)
//     Matrix<int> m;

//     for (size_t i = 1; i < 10; ++i)
//     {
//         for (size_t j = 1; j < 10; ++j)
//         {
            

//         }
//     }

// END_TEST

BEGIN_SUITE(exam_tests)
    TEST(string_tests)
    TEST(store_tests)
    TEST(vector_tests)

END_SUITE