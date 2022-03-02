#include "mu_test.h"
#include "blocking_queue.hpp"
#include "thread.hpp"
#include <iostream>
#include <cassert>

class Cat{
public:
    void walk() const { std::cout << "walk the cat\n"; }
};

BEGIN_TEST(queue_int_test_ctor)
    mt::BlockingQueue<int> q;
    ASSERT_EQUAL(q.getCapacity(), 10);
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_EQUAL(q.getFront(), 0);
    ASSERT_EQUAL(q.getBack(), 0);

END_TEST

BEGIN_TEST(queue_int_test_size_and_capacity)
    mt::BlockingQueue<int> q(3);
    ASSERT_EQUAL(q.isEmpty(), true);
    ASSERT_EQUAL(q.getCapacity(), 3);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_enqueue)
    mt::BlockingQueue<int> q(10);
    for(size_t i = 1; i <= q.getCapacity(); i++)
    {
        q.enqueue(i);
        ASSERT_EQUAL(q.getBack(), (int)i);
    }
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_dequeue)
    mt::BlockingQueue<int> q(10);
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
    mt::BlockingQueue<int> q(3);
    ASSERT_EQUAL(q.isEmpty(), true);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.isEmpty(), false);

END_TEST


BEGIN_TEST(queue_int_isFull)
    mt::BlockingQueue<int> q(3);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    ASSERT_EQUAL(q.size(), 3);
    ASSERT_EQUAL(q.isFull(), true);

END_TEST

BEGIN_TEST(queue_int_test_copy_ctor)
    mt::BlockingQueue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    mt::BlockingQueue<int> q2(3);
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
    mt::BlockingQueue<Cat> qc;  
    ASSERT_EQUAL(qc.getCapacity(), 10);
    ASSERT_EQUAL(qc.size(), 0);

END_TEST


BEGIN_TEST(queue_Cat_test_size_and_capacity)
    mt::BlockingQueue<Cat> qc;
    Cat tom,andy,jerry;
    qc.enqueue(tom);
    qc.enqueue(andy);
    qc.enqueue(jerry);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.getCapacity(), 10);

END_TEST


BEGIN_TEST(queue_Cat_test_enqueue)
    mt::BlockingQueue<Cat> qc(64);  
    Cat kitten;
    qc.enqueue(kitten);
    ASSERT_EQUAL(qc.size(), 1);
    qc.dequeue();
    ASSERT_EQUAL(qc.size(), 0);

END_TEST

BEGIN_TEST(queue_Cat_test_dequeue)
    mt::BlockingQueue<Cat> qc(3);
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
    mt::BlockingQueue<Cat> qc(3);
    ASSERT_EQUAL(qc.isEmpty(), true);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    ASSERT_EQUAL(qc.isEmpty(), false);

END_TEST


BEGIN_TEST(queue_Cat_isFull)
    mt::BlockingQueue<Cat> qc(3);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    ASSERT_EQUAL(qc.size(), 3);
    ASSERT_EQUAL(qc.isFull(), true);

END_TEST

BEGIN_TEST(queue_Cat_test_copy_ctor)
    mt::BlockingQueue<Cat> qc(3);
    Cat a,b,c;
    qc.enqueue(a);
    qc.enqueue(b);
    qc.enqueue(c);
    mt::BlockingQueue<Cat> q2;
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
    mt::BlockingQueue<int> qi;
    mt::BlockingQueue<mt::BlockingQueue<int> > qqi(2);  
    ASSERT_EQUAL(qqi.isEmpty(), true);
    ASSERT_EQUAL(qqi.getCapacity(), 2);
    ASSERT_EQUAL(qqi.size(), 0);
    ASSERT_EQUAL(qqi.isFull(), false);

END_TEST

//MUTEX + THREAD TESTS

mt::BlockingQueue<int> q;
const size_t N = 1000;
mt::Mutex mtx;

void* FillFIrstHalfWithoutMutex(void*)
{   
    for (size_t i = 0; i < N/2; i++)
    {
        q.enqueue(i);
    }

    return 0;
}

void* FillSecondHalfWithoutMutex(void*)
{   
    for (size_t i = N/2; i < N; i++)
    {
        q.enqueue(i);
    }

    return 0;
}

void* FillFIrstHalfWithMutex(void*)
{   
    for (size_t i = 0; i < N/2; i++)
    {
        mtx.lock();
        q.enqueue(i);
        mtx.unlock();
    }

    return 0;
}

void* FillSecondHalfWithMutex(void*)
{   
    for (size_t i = N/2; i < N; i++)
    {
        mtx.lock();
        q.enqueue(i);
        mtx.unlock();
    }

    return 0;
}

BEGIN_TEST(blocking_queue_fill_with_threads_without_mutex)
    mt::Thread th1(FillFIrstHalfWithMutex);
    mt::Thread th2(FillSecondHalfWithMutex);

    th1.join();
    th2.join();

    q.print();
    ASSERT_EQUAL(q.size(), 1000);
    
END_TEST


BEGIN_TEST(blocking_queue_fill_without_threads_without_mutex)
    mt::Thread th1(FillFIrstHalfWithoutMutex);
    mt::Thread th2(FillSecondHalfWithoutMutex);

    th1.join();
    th2.join();

    q.print();
    ASSERT_NOT_EQUAL(q.size(), 1000);
    
END_TEST


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

    TEST(queue_of_queue_int_test_ctor)
    TEST(blocking_queue_fill_with_threads_without_mutex)

END_SUITE