#include "mu_test.h"
#include "sorted_vector.hpp"
#include "sorted_list.hpp"
#include <iostream>

BEGIN_TEST(sorted_vector_print)
    const size_t N = 10;

    cpp::SortedVector v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(rand() % 100);
    }

    v.print(std::cout);

END_TEST 


BEGIN_TEST(sorted_vector_insert)
    const size_t N = 1000;

    cpp::SortedVector v(1000);

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.size(), 1000);

END_TEST  


BEGIN_TEST(sorted_vector_random_int_sort)
    const size_t N = 1000;

    cpp::SortedVector v(1000);

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(rand() % 100);
    }

    int first = v.front();
    int second = v.front();
    for (size_t i = 1; i <= N; ++i)
    {
        ASSERT_THAT(first <= second);
        v.remove(first);
        first = v.front();
        v.remove(second);
        second = v.front();
    }

    ASSERT_EQUAL(v.size(), 1000);

END_TEST  


BEGIN_TEST(sorted_vector_contains)
    const size_t N = 1000;

    cpp::SortedVector v(1000);

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.contains(666), true);
    ASSERT_EQUAL(v.contains(6666), false);

END_TEST 


BEGIN_TEST(sorted_vector_front_and_back)
    const size_t N = 1000;

    cpp::SortedVector v(1000);

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.front(), 1);
    ASSERT_EQUAL(v.back(), 1000);

END_TEST 


BEGIN_TEST(sorted_list_print)
    const size_t N = 10;

    cpp::SortedList l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(rand() % 100);
    }

    l.print(std::cout);

END_TEST 


BEGIN_TEST(sorted_list_insert)
    const size_t N = 1000;

    cpp::SortedList l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.size(), 1000);

END_TEST  


BEGIN_TEST(sorted_list_random_int_sort)
    const size_t N = 1000;

    cpp::SortedList l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(rand() % 100);
    }

    int first;
    int second;
    for (size_t i = 1; i < N-1; ++i)
    {
        first = l.front();
        l.remove(first);
        second = l.front();
        l.remove(second);
        
        ASSERT_THAT(first <= second);
    }

    ASSERT_EQUAL(l.size(), 0);

END_TEST  


BEGIN_TEST(sorted_list_contains)
    const int N = 1000;

    cpp::SortedList l;

    ASSERT_EQUAL(l.size(), 0);

    for (int i = 1; i <= N; ++i)
    {
        l.insert(i);
    }
    ASSERT_EQUAL(l.size(), N);
    ASSERT_EQUAL(l.contains(666), true);
    ASSERT_EQUAL(l.contains(6666), false);

END_TEST 


BEGIN_TEST(sorted_list_front_and_back)
    const size_t N = 1000;

    cpp::SortedList l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 1000);

END_TEST 

BEGIN_TEST(sorted_container)
    const size_t N = 1000;
    const size_t E = 2000;

    using namespace cpp;
    using namespace std;

    vector<SortedContainer*> sc;

    SortedVector v;
    for (size_t i = 1; i <= N; i++)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.size(), 1000);

    SortedList l;
    for (size_t i = N+1; i <= E; i++)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.size(), 1000);

    sc.push_back(&v);
    sc.push_back(&l);

    ASSERT_EQUAL(sc.size(), 2);

    vector<SortedContainer*>::const_iterator it = sc.begin();
    vector<SortedContainer*>::const_iterator end = sc.end();

    // size_t totalSize = 0;
    bool isNumFound;
    int n1 = 666;
    while(it != end)
    {        
        SortedContainer* pc = *it++;
        if(pc->contains(n1))
        {
            isNumFound = true;
            break;
        }
    }

    ASSERT_EQUAL(isNumFound, true);

    it = sc.begin();
    int n2 = 1234;
    while(it != end)
    {        
        SortedContainer* pc = *it++;
        if(pc->contains(n2))
        {
            isNumFound = true;
            break;
        }
    }

    it = sc.begin();
    size_t totalSize = 0;
    while(it != end)
    {        
        SortedContainer* pc = *it++;
        totalSize += pc->size();
    }

    ASSERT_EQUAL(totalSize, 2000);

END_TEST 


BEGIN_SUITE(sorted_list_tests)
    TEST(sorted_vector_print)
    TEST(sorted_vector_insert)
    TEST(sorted_vector_random_int_sort)
    TEST(sorted_vector_contains)
    TEST(sorted_vector_front_and_back)

    TEST(sorted_list_print)
    TEST(sorted_list_insert)
    TEST(sorted_list_random_int_sort)
    TEST(sorted_list_contains)
    TEST(sorted_list_front_and_back)

    TEST(sorted_container)
    
END_SUITE