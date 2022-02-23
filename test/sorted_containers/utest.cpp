#include "mu_test.h"
#include "sorted_vector.hpp"
#include "sorted_list.hpp"
#include <iostream>

BEGIN_TEST(sorted_vector_print)
    const size_t N = 10;

    cpp::SortedVector<int> v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(rand() % 100);
    }

    v.print(std::cout);

END_TEST 


BEGIN_TEST(sorted_vector_insert)
    const size_t N = 10;

    cpp::SortedVector<int> v(1000);

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.size(), 10);

END_TEST  


BEGIN_TEST(sorted_vector_random_int_sort)
    const size_t N = 10;

    cpp::SortedVector<int> v(1000);

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

    ASSERT_EQUAL(v.size(), 0);

END_TEST  


BEGIN_TEST(sorted_vector_contains)
    const size_t N = 1000;

    cpp::SortedVector<int> v(1000);

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

    cpp::SortedVector<int> v(1000);

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

    cpp::SortedList<int> l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(rand() % 100);
    }

    l.print(std::cout);

END_TEST 


BEGIN_TEST(sorted_list_insert)
    const size_t N = 1000;

    cpp::SortedList<int> l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.size(), 1000);

END_TEST  


BEGIN_TEST(sorted_list_random_int_sort)
    const size_t N = 1000;

    cpp::SortedContainer<int>* l = new cpp::SortedList<int>;

    ASSERT_EQUAL(l->size(), 0);

    srand(time(NULL));
    for (size_t i = 1; i <= N; ++i)
    {
        l->insert((std::rand() % 100) +1);
    }

    ASSERT_EQUAL(l->size(), 1000);

    int first;
    int second;
    for (size_t i = 1; i < N-1; ++i)
    {
        first = l->front();
        l->remove(first);
        second = l->front();
        l->remove(second);
        ASSERT_THAT(first <= second);
    }

    ASSERT_EQUAL(l->size(), 0);

END_TEST  


BEGIN_TEST(sorted_list_contains)
    const int N = 1000;

    cpp::SortedList<int> l;

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

    cpp::SortedList<int> l;

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

    vector<SortedContainer<int>*> sc;

    SortedVector<int> v;
    for (size_t i = 1; i <= N; i++)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.size(), 1000);

    SortedList<int> l;
    for (size_t i = N+1; i <= E; i++)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.size(), 1000);

    sc.push_back(&v);
    sc.push_back(&l);

    ASSERT_EQUAL(sc.size(), 2);

    vector<SortedContainer<int>*>::const_iterator it = sc.begin();
    vector<SortedContainer<int>*>::const_iterator end = sc.end();

    bool isNumFound;
    int n1 = 666;
    while(it != end)
    {        
        SortedContainer<int>* pc = *it++;
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
        SortedContainer<int>* pc = *it++;
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
        SortedContainer<int>* pc = *it++;
        totalSize += pc->size();
    }

    ASSERT_EQUAL(totalSize, 2000);

END_TEST 


BEGIN_TEST(test_heap_allocated)
    using cpp::SortedContainer;
    using cpp::SortedVector;

    SortedContainer<int>* container = new cpp::SortedList<int>();

    ASSERT_THAT(container->empty());
    fill(*container, -10, 28, 4);

    cpp::SortedList<int> list;
    ASSERT_THAT(list.empty());

    SortedContainer<int>& cr = list;
    fill(cr, 56, -10, -3);

    TRACER << *container << "\n";
    TRACER << cr << "\n";
    delete container;

    container = new SortedVector<int>();
    fill(*container, 10, 150, 10);

    TRACER << *container << "\n";
    delete container;

END_TEST


BEGIN_TEST(sorted_vector_fill)
    const size_t N = 1000;

    using cpp::SortedContainer;
    using cpp::SortedVector;

    SortedContainer<int>* container = new SortedVector<int>();

    for (size_t i = 1; i <= N; ++i)
    {
        container->fill(i, 2);    
    }

    ASSERT_EQUAL(container->size(), N*2);
    size_t count = 0;
    for (size_t i = 0; i <= N; ++i)
    {
        count += container->remove(i);
    }

    ASSERT_EQUAL(count, 2000);
    ASSERT_EQUAL(container->size(), 0);
    
    delete container;

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
    TEST(test_heap_allocated)

    TEST(sorted_vector_fill)
    
END_SUITE