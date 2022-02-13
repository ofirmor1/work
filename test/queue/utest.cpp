#include "mu_test.h"
#include "queue.hpp"
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

class Cat{
public:
    void walk() const { std::cout << "walk the cat\n"; }
};

BEGIN_TEST(queue_int_test_ctor)
    Queue<int> q;
    ASSERT_EQUAL(q.getCapacity(), 10);
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_EQUAL(q.getFront(), 0);
    ASSERT_EQUAL(q.getBack(), 0);

END_TEST

BEGIN_TEST(queue_int_test_size_and_capacity)
    Queue<int> q(3);
    ASSERT_EQUAL(q.isEmpty(), true);
    ASSERT_EQUAL(q.getCapacity(), 3);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_enqueue)
    Queue<int> q(10);
    for(size_t i = 1; i <= q.getCapacity(); i++)
    {
        q.enqueue(i);
        ASSERT_EQUAL(q.getBack(), (int)i);
    }
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_dequeue)
    Queue<int> q(10);
    for(size_t i = 1; i <= q.getCapacity(); i++)
    {
        q.enqueue(i);
        ASSERT_EQUAL(q.getBack(), (int)i);
    }
    ASSERT_EQUAL(q.size(), 10);
    for(size_t i = 1; i <= q.getCapacity(); i++)
    {
        int item = q.dequeue();
        ASSERT_EQUAL(item, (int)i);
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
    Queue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    Queue<int> q2(3);
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
    ASSERT_EQUAL(q2.size(), 0);
    ASSERT_EQUAL(q2.isEmpty(), true);

END_TEST

//queue of cats tests

BEGIN_TEST(queue_Cat_test_ctor)
    Queue<Cat> qc;  
    ASSERT_EQUAL(qc.getCapacity(), 10);
    ASSERT_EQUAL(qc.size(), 0);

END_TEST


BEGIN_TEST(queue_Cat_test_size_and_capacity)
    Queue<Cat> qc;
    Cat tom,andy,jerry;
    qc.enqueue(tom);
    qc.enqueue(andy);
    qc.enqueue(jerry);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.getCapacity(), 10);

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


BEGIN_TEST(queue_Cat_isEmpty)
    Queue<Cat> qc(3);
    ASSERT_EQUAL(qc.isEmpty(), true);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    ASSERT_EQUAL(qc.isEmpty(), false);

END_TEST


BEGIN_TEST(queue_Cat_isFull)
    Queue<Cat> qc(3);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.isFull(), true);

END_TEST

BEGIN_TEST(queue_Cat_test_copy_ctor)
    Queue<Cat> qc(3);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    Queue<Cat> q2;
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(q2.size(), 0);
    q2 = qc;
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(q2.size(), 3);
    Cat isA = q2.dequeue();
    Cat isB = q2.dequeue();
    Cat isC = q2.dequeue();
    (void)isA;
    (void)isB;
    (void)isC;
    // ASSERT_EQUAL(isA, a);


END_TEST


// queue of queue of int tests
BEGIN_TEST(queue_of_queue_int_test_ctor)
    Queue<int> qi;
    Queue<Queue<int> > qqi(2);  
    ASSERT_EQUAL(qqi.isEmpty(), true);
    ASSERT_EQUAL(qqi.getCapacity(), 2);
    ASSERT_EQUAL(qqi.size(), 0);
    ASSERT_EQUAL(qqi.isFull(), false);

END_TEST


BEGIN_TEST(queue_of_queue_int_test_enqueue)
    Queue<int> qi1;
    Queue<int> qi2;
    Queue<Queue<int> > qqi(3);  
    ASSERT_EQUAL(qqi.isEmpty(), true);
    ASSERT_EQUAL(qqi.getCapacity(), 3);
    qi1.enqueue(1);
    qi1.enqueue(3);
    qi1.enqueue(5);
    qi2.enqueue(2);
    qi2.enqueue(4);
    qi2.enqueue(6);
    qqi.enqueue(qi1);
    // qqi.dequeue();
    // qqi.enqueue(qi1);
    printf("check\n");
    ASSERT_EQUAL(qqi.size(), 1);
    qqi.getFront().print();

END_TEST

BEGIN_TEST(queue_of_queue_int_test_dequeue)
    Queue<int> qi1;
    Queue<int> qi2;
    Queue<Queue<int> > qqi(3);  
    ASSERT_EQUAL(qqi.isEmpty(), true);
    ASSERT_EQUAL(qqi.getCapacity(), 3);
    qi1.enqueue(1);
    qi1.enqueue(3);
    qi1.enqueue(5);
    qi2.enqueue(2);
    qi2.enqueue(4);
    qi2.enqueue(6);
    qqi.enqueue(qi1);
    qqi.enqueue(qi2);
    qqi.dequeue();
    qqi.dequeue();
    ASSERT_EQUAL(qqi.size(), 0);
    qqi.getFront().print();
END_TEST


// BEGIN_TEST(queue_of_queue_int_isEmpty)
//     Queue<Cat> qc(3);
//     ASSERT_EQUAL(qc.isEmpty(), true);
//     Cat a,b,c;
//     qc.enqueue(a);
//     qc.enqueue(b);
//     qc.enqueue(c);
//     ASSERT_EQUAL(qc.isEmpty(), false);

// END_TEST


// BEGIN_TEST(queue_of_queue_int_isFull)
//     Queue<Cat> qc(3);
//     Cat a,b,c;
//     qc.enqueue(a);
//     qc.enqueue(b);
//     qc.enqueue(c);
//     ASSERT_EQUAL(qc.size(), 3);
//     ASSERT_EQUAL(qc.isFull(), true);

// END_TEST


// BEGIN_TEST(queue_of_queue_int_test_copy_ctor)
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
//     for(size_t i = 1; i <= q.size(); i++)
//     {
//         int r = q2.dequeue();
//         ASSERT_EQUAL(r, (int)i);
//     }

// END_TEST

BEGIN_SUITE(queue_tests_unit)
    //queue of int tests
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
    TEST(queue_Cat_isEmpty)
    TEST(queue_Cat_isFull)
    TEST(queue_Cat_test_copy_ctor)

    //queue of quee of int
    TEST(queue_of_queue_int_test_ctor)
    TEST(queue_of_queue_int_test_enqueue)
    TEST(queue_of_queue_int_test_dequeue)
    // TEST(queue_of_queue_int_isEmpty)
    // TEST(queue_of_queue_int_isFull)
    // TEST(queue_of_queue_int_test_copy_ctor)
    
END_SUITE