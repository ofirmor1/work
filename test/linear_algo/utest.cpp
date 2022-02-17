#include "mu_test.h"
#include "linear_algo.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include <iostream>
#include <cassert>
#include <cmath>


using namespace cpp;
using std::vector;
using std::ceil;

BEGIN_TEST(chaos_with_rand_double)
    vector<double> myvec(100);

    Chaos(myvec);

    for (size_t i = 0 ; i < myvec.size(); i++)
    {
        std::cout << myvec[i] << std::endl;
    }
    
    ASSERT_PASS();

END_TEST   


BEGIN_TEST(sum_of_double_elements_in_vector)
    vector<double> myvec(100);

    Chaos(myvec);

    double sum = sumElements(myvec);

    cout << "\nsum of elements in vector: " << sum;
    cout << "\n" << endl;

    sum = 0;
    ASSERT_EQUAL(sum, 0);
    sum = simpleSum(myvec);

    cout << "simpleSum of elements in vector: " << sum;
    cout << "\n" << endl;

    ASSERT_PASS();

END_TEST    

BEGIN_TEST(remove_odd_elements_from_vector_of_int)
    vector<int> myvec(0);

    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    myvec.push_back(5);

    ASSERT_EQUAL(myvec.size(), 5);

    oddsOut(myvec);
    ASSERT_EQUAL(myvec.size(), 3);
    ASSERT_EQUAL(myvec[0], 1);
    ASSERT_EQUAL(myvec[1], 3);
    ASSERT_EQUAL(myvec[2], 5);


    ASSERT_PASS();

END_TEST    


BEGIN_TEST(extreme_find_min_and_max_values_in_vector)
    vector<int> myvec(0);
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    myvec.push_back(5);
    pair<int,int> vecElements = extremes(myvec);
    ASSERT_EQUAL(vecElements.first, 1);
    ASSERT_EQUAL(vecElements.second, 5);

END_TEST


// BEGIN_TEST(find_first_duplicate_element_in_vector)
//     vector<Ball> myvec(0);
//     myvec.push_back(Ball("red", 3));
//     myvec.push_back(Ball("blue", 2));
//     myvec.push_back(Ball("green", 2));
//     myvec.push_back(Ball("yellow", 4));
//     myvec.push_back(Ball("gray", 3));
//     // cout << myvec[3].getRadius() << endl;
//     size_t duplicateIndex = firstDuplicate(myvec);
//     printf("%ld \n", duplicateIndex);
//     ASSERT_PASS();

// END_TEST


BEGIN_SUITE(linear_algo_tests)
    TEST(chaos_with_rand_double)
    TEST(sum_of_double_elements_in_vector)
    TEST(remove_odd_elements_from_vector_of_int)
    TEST(extreme_find_min_and_max_values_in_vector)
    // TEST(find_first_duplicate_element_in_vector)
    
END_SUITE