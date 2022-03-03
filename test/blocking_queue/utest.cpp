#include "mu_test.h"
#include "blocking_queue.hpp"
#include "thread.hpp"
#include <iostream>
#include <cassert>
#include <unistd.h>

//MUTEX + THREAD TESTS

mt::BlockingQueue<int> q;
const int LOOPS = 10;

void* producer(void*)
{   
    bool ok = false;
    for (size_t i = 0; i < LOOPS;)
    {
        printf("%ld\n", i);
        ok = q.enqueue(i, ok);
        if(ok)
        {
            ++i;
        }    
        else
        {
            usleep(500000);
        }
    }

    return 0;
}

template<typename T>
void* consumer(void*)
{   
    std::pair<T, bool> pair;
    for (int i = 0; i < LOOPS; i++)
    {
        bool ok = false;
        pair = q.dequeue(ok);
        if(pair.second == ok)
        {
            if(pair.first == i)
            {
                ++i;
            }
            else
            {
                break;
            }
        }
        else
        {
            usleep(2000000);
        }
    }

    return 0;
}


BEGIN_TEST(test_mutex_with_2cons_2prod)
    mt::Thread p1(producer, 0);
    mt::Thread p2(producer, 0);
    mt::Thread c1(consumer<int>, 0);
    mt::Thread c2(consumer<int>, 0);

    p1.join();
    p2.join();
    c1.join();
    c2.join();
    ASSERT_PASS();
    // ASSERT_EQUAL(q.size(), 0);
    
END_TEST


void* fillPositive(void*)
{
    mt::BlockingQueue<int> q;

    bool ok = false;
    for (size_t i = 1; i < LOOPS;)
    {
        printf("%ld\n", i);
        ok = q.enqueue(i, ok);
        if(ok)
        {
            ++i;
        }    
        else
        {
            usleep(50000000);
        }
    }

    return 0;
}

void* fillNegative(void*)
{
    mt::BlockingQueue<int> q;

    bool ok = false;
    for (int i = 0; i > -1*LOOPS;)
    {
        printf("%d\n", i);
        ok = q.enqueue(i, ok);
        if(ok)
        {
            --i;
        }  
        else
        {
            usleep(50000000);
        }  
    }

    return 0;
}

template<typename T>
void* clearQueue(void*)
{
    mt::BlockingQueue<int> q;

    bool ok = false;
    for (int i = 0; i < 2*LOOPS;)
    {
        printf(" 123  ");
        
        std::pair<T,bool> p = q.dequeue(ok);
        printf("%d\n 123", p.first);
        // int neg = i*-1;
        // int pos = i;
        if(p.second == ok)
        {   
            if(p.first == i)
            {
                ++i;
            }
            else
            {
                break;
            }
        }
        else
        {
            usleep(50000000);
        }   
    }

    return 0;
}

BEGIN_TEST(test_mutex_with_2th_fill_1th_dequeue)
    mt::Thread f1(fillPositive, 0);
    mt::Thread f2(fillNegative, 0);
    // mt::Thread c1(clearQueue<int>, 0);

    f1.join();
    f2.join();
    // c1.join();

    ASSERT_EQUAL(q.size(), 0);
    
END_TEST


BEGIN_SUITE(queue_tests_unit)

    TEST(test_mutex_with_2cons_2prod)
    TEST(test_mutex_with_2th_fill_1th_dequeue)

END_SUITE