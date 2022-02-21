#include "mu_test.h"
#include "linear_algo.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include <iostream>
#include <cassert>
#include <cmath>


using namespace cpp;

BEGIN_TEST(chaos_with_rand_double)
    std::vector<double> myvec(100);

    Chaos(myvec);

    for (size_t i = 0 ; i < myvec.size(); i++)
    {
        std::cout << myvec[i] << std::endl;
    }
    
    ASSERT_PASS();

END_TEST   


BEGIN_TEST(sum_of_double_elements_in_vector)
    std::vector<double> myvec(100);

    Chaos(myvec);

    double sum = sumElements(myvec);

    std::cout << "\nsum of elements in vector: " << sum;
    std::cout << "\n" << std::endl;

    sum = 0;
    ASSERT_EQUAL(sum, 0);
    sum = simpleSum(myvec);

    std::cout << "simpleSum of elements in vector: " << sum;
    std::cout << "\n" << std::endl;

    ASSERT_PASS();

END_TEST    

BEGIN_TEST(remove_odd_elements_from_vector_of_int)
    const size_t N = 1000;
    std::vector<size_t> myvec(0);

    for (size_t i = 1; i < N; ++i)
    {
        myvec.push_back(i);
        ASSERT_EQUAL(myvec[i-1], i);
    }

    ASSERT_EQUAL(myvec.size(), 999);

    oddsOut(myvec);

    ASSERT_EQUAL(myvec.size(), 499);

    size_t j = 2;
    for (size_t i = 1; i < N/2; i++)
    {
        myvec.pop_back();
        ASSERT_EQUAL(myvec[i-1], j);
        j += 2;
    }

    ASSERT_EQUAL(myvec.size(), 0);

END_TEST    


BEGIN_TEST(extreme_find_min_and_max_values_in_vector)
    const size_t N = 1000;
    std::vector<size_t> myvec(0);

    for (size_t i = 1; i < N; ++i)
    {
        myvec.push_back(i);
        ASSERT_EQUAL(myvec[i-1], i);
    }

    myvec[500] = 1000;

    std::pair<int,int> vecElements = extremes(myvec);
    ASSERT_EQUAL(vecElements.first, 1);
    ASSERT_EQUAL(vecElements.second, 1000);

END_TEST


BEGIN_TEST(find_first_duplicate_element_in_vector)
    std::vector<Ball> vec;
    const size_t N = 10;
    size_t r1 = 1;
    size_t r2 = 2;
    for (size_t i = 1; i < N; i++)
    {
        vec.push_back(Ball("white", i));
        if(i == 3)
        {
            vec.push_back(Ball("white", r1));
        }
        if(i == 4)
        {
            vec.push_back(Ball("white", r2));
        }
    }
    
    // cout << myvec[3].getRadius() << endl;
    size_t duplicateIndex = cpp::firstDuplicate(vec);
    ASSERT_EQUAL(duplicateIndex, 3);   

END_TEST


BEGIN_TEST(common_elements_in_v1_and_v2_not_v3_vectors)
    const size_t N = 1000;
    std::vector<int> vec1(0);
    for (size_t i = 1; i < N; i++)
    {
        vec1.push_back(i);
    }
    
    std::vector<int> vec2(0);

    for (size_t i = 3; i < N; i++)
    {
        vec2.push_back(i);
    }
    
    std::vector<int> vec3(0);

    for (size_t i = 10; i < N-3; i++)
    {
        vec3.push_back(i);
    }

    size_t common = countCommontStrange(vec1, vec2, vec3);

    ASSERT_EQUAL(common, 10);

    std::vector<int> vec4(0);

    for (size_t i = 3; i < N; i++)
    {
        vec2.push_back(i);
    }

    size_t common2 = countCommontStrange2(vec1, vec2, vec3);

    ASSERT_EQUAL(common2, 10);
    
END_TEST


BEGIN_TEST(first_unique_in_vector)
    const size_t N = 10;

    std::vector<int> v;

    for (size_t i = 0; i < N; i++)
    {
        v.push_back(i);
    }

    v[5] = 3;
    v[7] = 4;

    size_t first = findFirstUnique(v);
    ASSERT_EQUAL(first, 3);

END_TEST
BEGIN_SUITE(linear_algo_tests)
    TEST(chaos_with_rand_double)
    TEST(sum_of_double_elements_in_vector)
    TEST(remove_odd_elements_from_vector_of_int)
    TEST(extreme_find_min_and_max_values_in_vector)
    TEST(find_first_duplicate_element_in_vector)
    TEST(common_elements_in_v1_and_v2_not_v3_vectors)
    TEST(first_unique_in_vector)
    
END_SUITE