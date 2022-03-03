#include "mu_test.h"
#include "para_algo.hpp"

#include<vector>
#include <pthread.h>
#include <numeric>

BEGIN_TEST(sum_vector_of_1000_elements_with_one_threads)
	using namespace cpp;

    std::vector<int> v;

    for(size_t i = 1; i <= 1000; ++i)
    {
        v.push_back(i);
    }
   
    size_t sum = sumVector(v, 1);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1000_elements_with_two_threads)
	using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 2);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1000_elements_with_four_threads)
	using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 4);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1000_elements_with_sixteen_threads)
	using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 16);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1M_elements_with_one_threads)
    using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 1);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1M_elements_with_two_threads)
    using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 2);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1M_elements_with_four_threads)
    using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 4);
	std::cout<< sum << std::endl;
	ASSERT_PASS();

END_TEST


BEGIN_TEST(sum_vector_of_1M_elements_with_sixteen_threads)
    using namespace cpp;

    std::vector<int> vec;

    for(size_t i = 1; i <= 1000000; ++i)
    {
        vec.push_back(i);
    }
   
    size_t sum = sumVector(vec, 16);
	std::cout<< sum  << std::endl;
	ASSERT_PASS();

END_TEST

template <typename T>   
void printElm(std::vector<T> a_vec)
{
    for (size_t i = 0; i < a_vec.size(); i++)
    {
        std::cout << a_vec[i] << std::endl;
    }
}

// BEGIN_TEST(sort_vector_of_1000_elements_with_one_threads)
// 	using namespace cpp;

//     std::vector<int> v;

//     for(size_t i = 1; i <= 1000; ++i)
//     {
//         v.push_back(random()%100);
//     }
   
//     sortVector(v, 1);
// 	printElm(v);
// 	ASSERT_PASS();

// END_TEST


BEGIN_SUITE(para_algo_tests)
    TEST(sum_vector_of_1000_elements_with_one_threads)
    TEST(sum_vector_of_1000_elements_with_two_threads)
    TEST(sum_vector_of_1000_elements_with_four_threads)
    TEST(sum_vector_of_1000_elements_with_sixteen_threads)

    TEST(sum_vector_of_1M_elements_with_one_threads)
    TEST(sum_vector_of_1M_elements_with_two_threads)
    TEST(sum_vector_of_1M_elements_with_four_threads)
    TEST(sum_vector_of_1M_elements_with_sixteen_threads)

    // TEST(sort_vector_of_1000_elements_with_one_threads)

END_SUITE   
