#include "mu_test.h"
#include "queue.hpp"
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

BEGIN_TEST(queue_int_test_ctor)
    Queue<int> q;
    ASSERT_EQUAL(q.cap(), 10);
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_EQUAL(q.getBack(), 0);
    ASSERT_EQUAL(q.getFront(), 0);

END_TEST

BEGIN_TEST(queue_int_test_size_and_capacity)
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q.cap(), 10);

END_TEST

BEGIN_TEST(queue_int_test_enqueue)
    Queue<int> q(10);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);

END_TEST

BEGIN_TEST(queue_int_test_dequeue)
    Queue<int> q(10);
    for(size_t i = 1; i <= q.size(); i++)
    {
        q.enqueue(i);
        ASSERT_EQUAL(q.size(), i);
    }
    q.enqueue(1);
    ASSERT_EQUAL(q.size(), 2); //?????
    for(size_t i = 1; i <= q.size(); i++)
    {
        size_t item = q.dequeue();
        ASSERT_EQUAL(item, i);
    }
    ASSERT_EQUAL(q.size(), 0);

END_TEST


BEGIN_TEST(queue_int_isEmpty)
    Queue<int> q(3);
    ASSERT_EQUAL(q.isEmpty(), true);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.isEmpty(), false);

END_TEST


BEGIN_TEST(queue_int_isFull)
    Queue<int> q(3);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_copy_ctor)
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    Queue<int> q2;
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q2.size(), 0);
    q2 = q;
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q2.size(), 3);
    for(size_t i = 1; i <= q.size(); i++)
    {
        size_t r = q2.dequeue();
        ASSERT_EQUAL(r, i);
    }

END_TEST

//queue of cats tests

BEGIN_TEST(queue_Cat_test_ctor)
    Queue<Cat> qc;  
    ASSERT_EQUAL(qc.cap(), 10);
    ASSERT_EQUAL(qc.size(), 0);
    ASSERT_EQUAL(qc.getBack(), 0);
    ASSERT_EQUAL(qc.getFront(), 0);

END_TEST


BEGIN_TEST(queue_Cat_test_size_and_capacity)
    Queue<Cat> qc;
    Cat tom,andy,jerry;
    qc.enqueue(tom);
    qc.enqueue(andy);
    qc.enqueue(jerry);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.cap(), 10);

END_TEST


BEGIN_TEST(queue_Cat_test_enqueue)
    Queue<Cat> qc(64);  
    Cat kitten;
    qc.enqueue(kitten);
    ASSERT_EQUAL(qc.size(), 1);
    qc.dequeue();
    ASSERT_EQUAL(qc.size(), 0);

END_TEST

BEGIN_TEST(queue_Cat_test_dequeue)
    Queue<Cat> qc(3);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.isFull(), true);
    qc.dequeue();
    qc.dequeue();
    qc.dequeue();
    ASSERT_EQUAL(qc.size(), 0);
    ASSERT_EQUAL(qc.isEmpty(), true);

END_TEST



// BEGIN_TEST(queue_Cat_isEmpty)
//     Queue<int> q(3);
//     ASSERT_EQUAL(q.isEmpty(), true);
//     q.enqueue(1);
//     q.enqueue(3);
//     q.enqueue(5);
//     ASSERT_EQUAL(q.isEmpty(), false);

// END_TEST


// BEGIN_TEST(queue_Cat_isFull)
//     Queue<int> q(3);
//     q.enqueue(1);
//     q.enqueue(3);
//     q.enqueue(5);
//     ASSERT_EQUAL(q.size(), 3);
//     ASSERT_EQUAL(q.isFull(), true);

// END_TEST

// BEGIN_TEST(queue_Cat_test_copy_ctor)
//     Queue<int> q;
//     q.enqueue(1);
//     q.enqueue(2);
//     q.enqueue(3);
//     Queue<int> q2;
//     ASSERT_EQUAL(q.size(), 3);
//     ASSERT_EQUAL(q2.size(), 0);
//     q2 = q;
//     ASSERT_EQUAL(q.size(), 3);
//     ASSERT_EQUAL(q2.size(), 3);
//     for(int i = 1; i <= q.size(); i++)
//     {
//         int r = q2.dequeue();
//         ASSERT_EQUAL(r, i);
//     }

// END_TEST


BEGIN_SUITE(queue_tests_unit)
    TEST(queue_int_test_ctor)
    TEST(queue_int_test_size_and_capacity)
    TEST(queue_int_test_enqueue)
    TEST(queue_int_test_dequeue)
    TEST(queue_int_isEmpty)
    TEST(queue_int_isFull)
    TEST(queue_int_test_copy_ctor)

    //queue of cats tests
    TEST(queue_Cat_test_ctor)
    TEST(queue_Cat_test_size_and_capacity)
    TEST(queue_Cat_test_enqueue)
    TEST(queue_Cat_test_dequeue)
    // TEST(queue_Cat_isEmpty)
    // TEST(queue_Cat_isFull)
    // TEST(queue_Cat_test_copy_ctor)
    

END_SUITE