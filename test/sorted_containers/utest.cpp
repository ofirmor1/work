#include "mu_test.h"
#include "sorted_vector.hpp"
#include "sorted_list.hpp"
#include "sorted_unique_vector.hpp"
#include "ball.hpp"
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

    // ContainerMedian(v);

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


BEGIN_TEST(test_sortedlist_ball_sorted)
    const size_t N = 1000;

    cpp::SortedList<Ball> balls;
    

    ASSERT_EQUAL(balls.size(), 0);
    ASSERT_EQUAL(balls.empty(), true);

    for (size_t i = 1; i <= N; ++i)
    {
        balls.insert(Ball("white", i));
    }

    ASSERT_EQUAL(balls.size(), 1000);
    ASSERT_EQUAL(balls.empty(), false);

    for (size_t i = 1; i <= N; ++i)
    {
        balls.remove(Ball("white,", i));
    }

    ASSERT_EQUAL(balls.size(), 0);
    ASSERT_EQUAL(balls.empty(), true);

    balls.fill(Ball("white", 10), 1);
    balls.fill(Ball("white", 4), 3);
    balls.fill(Ball("white", 16), 2);

    std::cout << balls << std::endl;

END_TEST


BEGIN_TEST(test_sorterd_vector_function_isSorted)
    const size_t N = 1000;

    cpp::SortedVector<int> v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i < N; ++i)
    {
        v.insert(rand() % 100);
    }

    ASSERT_EQUAL(v.isSorted(), true);

    v.insert(56);
    ASSERT_EQUAL(v.isSorted(), true);

    v.remove(56);
    ASSERT_EQUAL(v.isSorted(), true);

END_TEST


BEGIN_TEST(test_sorterd_vector_function_isUniform)
    const size_t N = 1000;

    cpp::SortedVector<int> v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(7);
    }

    ASSERT_EQUAL(v.isUniform(), true);

    v.insert(8);

    ASSERT_EQUAL(v.isUniform(), false);

END_TEST


BEGIN_TEST(test_sorterd_list_function_isSorted)
    const size_t N = 1000;

    cpp::SortedList<int> l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(rand() % 100);
    }
    
    ASSERT_EQUAL(l.isSorted(), true);

END_TEST


BEGIN_TEST(test_sorterd_list_function_isUniform)
    const size_t N = 1000;

    cpp::SortedList<int> l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        l.insert(7);
    }

    ASSERT_EQUAL(l.isUniform(), true);

    l.insert(8);

    ASSERT_EQUAL(l.isUniform(), false);

END_TEST


BEGIN_TEST(test_sorterd_vector_function_median)
    const size_t N = 11;

    cpp::SortedVector<int> v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i < N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.median(), 6);

END_TEST


BEGIN_TEST(test_sorterd_list_function_median)
    const size_t N = 11;

    cpp::SortedVector<int> l;

    ASSERT_EQUAL(l.size(), 0);

    for (size_t i = 1; i < N; ++i)
    {
        l.insert(i);
    }

    ASSERT_EQUAL(l.median(), 6);

END_TEST


BEGIN_TEST(test_sorterd_unique_vector)
    const size_t N = 1000;

    cpp::SortedUniqueVector<int> v;

    ASSERT_EQUAL(v.size(), 0);

    for (size_t i = 1; i <= N; ++i)
    {
        v.insert(i);
    }

    ASSERT_EQUAL(v.size(), 999);
    v.insert(4);
    ASSERT_EQUAL(v.size(), 999);

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
    TEST(test_sorterd_vector_function_isSorted)
    TEST(test_sorterd_vector_function_isUniform)
    TEST(test_sorterd_list_function_isSorted)
    TEST(test_sorterd_list_function_isUniform)
    TEST(test_sorterd_vector_function_median)
    TEST(test_sorterd_list_function_median)

    TEST(test_sortedlist_ball_sorted)

    TEST(test_sorterd_unique_vector)
    
END_SUITE