#include "mu_test.h"
#include "mutex_exceptions.hpp"
#include "thread_exceptions.hpp"
#include "blocking_queue_exceptions.hpp"
#include "blocking_queue.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include <stdio.h>

mt::Mutex m;
const size_t SIZE = 1000;
int tVar1 = -1; // testing fifo between 0-50
int tVar2 = 499; // testing fifo between 51-1000

template <typename T>
class Arguments
{

public:
    Arguments(mt::BlockingQueue<T> *a_queue, size_t a_begin, size_t a_end)
    : m_queue(a_queue)
    , m_begin(a_begin)
    , m_end(a_end)
    {}

    mt::BlockingQueue<T> *m_queue;
    size_t m_begin;
    size_t m_end;
};

void *enqueueMany(void *a_arg)
{
    using namespace mt;
    Arguments<int> *myArg = static_cast<Arguments<int> *>(a_arg);

    BlockingQueue<int> *queue = myArg->m_queue;
    size_t begin = myArg->m_begin;
    size_t end = myArg->m_end;
    size_t i = begin;
    bool isFull;
    try
    {
        while (i < end)
        {
            try
            {
                isFull = false;
                queue->enqueue(i);
            }
            catch(const std::exception& e)
            {
                isFull = true;
                std::cerr << e.what() << '\n';
            }
            m.lock();
            if(!isFull)
            {
                ++i;
            }
            m.unlock();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    
    return 0;
}

void *dequeueMany(void *a_arg)
{
    using namespace mt;
    int *arr = new int[SIZE];
    BlockingQueue<int> *queue = static_cast<BlockingQueue<int> *>(a_arg);

    bool isEmpty;
    try
    {
        size_t i = 0;
        while (i < SIZE)
        {
            try
            {
                isEmpty = false;
                queue->dequeue(arr[i]);
            }
            catch(const std::exception& e)
            {
                isEmpty = true;
                std::cerr << e.what() << '\n';
            }
            m.lock();
            if(!isEmpty)
            {
                ++i;
            }
            m.unlock();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }

    return arr;
}

bool ensureFIFO(int a_item)
{
    using namespace mt;
    try
    {
        if (a_item == tVar1 + 1)
        {
            m.lock();
            ++tVar1;
            m.unlock();
            return true;
        }
        if (a_item == tVar2 + 1)
        {
            m.lock();
            ++tVar2;
            m.unlock();
            return true;
        }
        return false;
    }
    catch(MutexAllreadyLocked const& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    catch(MutexAllreadyUnlocked const& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
}

BEGIN_TEST(fifo_test_one_thread_enque_one_dequeue)
using namespace mt;
try
{
    BlockingQueue<int> q(SIZE);
    Arguments<int> queueArg(&q, 0, SIZE);

    mt::Thread t1(0, enqueueMany, static_cast<void *>(&queueArg));
    mt::Thread t2(0, dequeueMany, static_cast<void *>(&q));

    t1.join();
    void *res = t2.join();
    int *y = static_cast<int *>(res);

    for (size_t i = 0; i < SIZE; ++i)
    {
        std::cout << y[i] <<",";
        ASSERT_EQUAL(y[i], (int)i);
    }
    ASSERT_EQUAL(q.isEmpty(), true);
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

END_TEST


BEGIN_TEST(fifo_test_two_thread_enque_one_dequeue)
using namespace mt;

BlockingQueue<int> q(SIZE);
Arguments<int> first(&q, 0, SIZE/2);
Arguments<int> second(&q, SIZE/2, SIZE);

mt::Thread t1(0, enqueueMany, static_cast<void *>(&first));
mt::Thread t2(0, enqueueMany, static_cast<void *>(&second));
mt::Thread t3(0, dequeueMany, static_cast<void *>(&q));

t1.join();
t2.join();
void *res = t3.join();
int *y = static_cast<int *>(res);

for (size_t i = 0; i < SIZE; ++i)
{
    std::cout << y[i] <<",";
    ASSERT_EQUAL(ensureFIFO(y[i]), true);
}
ASSERT_EQUAL(q.isEmpty(), true);

END_TEST


BEGIN_TEST(exceptions_test)
    mt::BlockingQueue<int> myQueue(2);
    ASSERT_EQUAL(myQueue.isEmpty(), true);
    int i;
    try 
    { 
        
        myQueue.dequeue(i);
         printf("123");
    }
    catch(BlockingQueueIsEmpty const& fail)
    {
        std::cerr << fail.what() << '\n';
        ASSERT_PASS();
    }
     printf("123");
    myQueue.enqueue(10);
    myQueue.enqueue(1);
     printf("123");
    try 
    { 
        myQueue.enqueue(7); 
        printf("123");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        ASSERT_PASS();
    }
    ASSERT_PASS();

END_TEST

BEGIN_SUITE(tests)
// TEST(fifo_test_one_thread_enque_one_dequeue)
// TEST(fifo_test_two_thread_enque_one_dequeue)
TEST(exceptions_test)

END_SUITE