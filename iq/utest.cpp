#include "mu_test.h"
#include "quest.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <vector>

using namespace iq;

static void printArr(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}

BEGIN_TEST(q1)
    int arr1[] = {1, 3, 4, 5, 7, 9, 12, 14};
    int arr2[] = {2, 6, 11, 15};

    size_t n = *(&arr1 + 1) - arr1;
    size_t k = *(&arr2 + 1) - arr2;

    printf("\nbefore:");
    printf("\narray1: ");
    printArr(arr1, n);
    printf("\narray2: ");
    printArr(arr2, k);

    mergeArr(arr1, arr2, n, k);

    printf("\nafter merge: \n");
    printArr(arr1, n);
    
    ASSERT_PASS();

END_TEST


BEGIN_TEST(q2)
    int arr[] = {1, 3, 4, 5, 7, 9, 12, 14};
    size_t n = *(&arr + 1) - arr;
    size_t k = 2;
    printf("\nbefore rotate: \n");
    printArr(arr, n);

    rotateArr(arr, n, k);

    printf("\nafter rotate: \n");
    printArr(arr, n);

    ASSERT_PASS();

END_TEST


BEGIN_TEST(q3)
    int arr[] = {5, 2, 0, 7, 9, 5, 2, 7};
    int n = *(&arr + 1) - arr;

    printf("\nbefore replace: \n");
    printArr(arr, n);
    
    replaceEachElmWIthLargestOnRight(arr, n);

    printArr(arr, n);

    printf("\nafter replace: \n");
    printArr(arr, n);

    ASSERT_PASS();

END_TEST


BEGIN_TEST(q4)
    int arr[] = {5, 2, 3, 7, 9, 5, 2, 7};
    int n = *(&arr + 1) - arr;

    printf("\nbefore replace: \n");
    printArr(arr, n);

    replaceEachElmWIthLargestOnRight(arr, n);

    printf("\nafter replace: \n");
    printArr(arr, n);

    ASSERT_PASS();

END_TEST


BEGIN_TEST(q5)
    size_t n = 7;
    int arr[7];
    
    nFirstPrime(n, arr);
    int* result = nFirstPrime(n, arr);
    printf("\n%ld first prime numbers: \n", n);
    printArr(result, n);
    
    ASSERT_PASS();

END_TEST


BEGIN_TEST(q6)
    int arr[] = { 0, 1, -1, -1, 0, 1, 0, -1, 0, 1 };

    size_t n = *(&arr + 1) - arr;
    
    printf("\nbefore sorting: \n");
    printArr(arr, n);
    
    sortArr(arr, n);

    printf("\nafter sorting: \n");
    printArr(arr, n);

    ASSERT_PASS();

END_TEST

BEGIN_TEST(q6_2)
    // int arr[] = { 0, 1, -1, -1, 0, 1, 0, -1, 0, 1 };
    std::vector<int> vec = { 0, 1, -1, -1, 0, 1, 0, -1, 0, 1 };
    // for(auto e : arr)
    // {
    //     vec.push_back(e);
    // }

    size_t n = vec.size();
    
    printf("\nbefore sorting: \n");
    for (auto e : vec)
    {
        std::cout << e << ' ' << '\n';
    }
    
    sortArr2(vec, n);

    printf("\nafter sorting: \n");
    for (auto e : vec)
    {
        std::cout << e << ' ' << '\n';
    }

    ASSERT_PASS();

END_TEST


BEGIN_TEST(q7)
    int num = 8;
    size_t setBits = numOfSetBits(num);
    printf("\nnum of set bits in num %d: %ld\n", num, setBits);

    ASSERT_EQUAL(setBits, 1);

    int num2 = 7;
    setBits = numOfSetBitsLUT(num2);
    printf("\nLUT Solution: num of set bits in num %d: %ld\n", num2, setBits);

    ASSERT_EQUAL(setBits, 3);
END_TEST



BEGIN_TEST(q8)
    int num = 19;//10011
    size_t setPairBits = numOfPairSetBits(num);
    printf("\nnum of set bits in num %d: %ld\n", num, setPairBits);

    ASSERT_EQUAL(setPairBits, 1);

    setPairBits = numOfPairSetBitsLUT(num);
    printf("\nLUT Solution:num of set bits in num %d: %ld\n", num, setPairBits);

    ASSERT_EQUAL(setPairBits, 1);

END_TEST

BEGIN_TEST(q9)
END_TEST

BEGIN_SUITE(iq_tests)
    TEST(q1)
    TEST(q2)
    TEST(q3)
    TEST(q4)
    TEST(q5)
    TEST(q6)
    TEST(q7)
    TEST(q8)
END_SUITE