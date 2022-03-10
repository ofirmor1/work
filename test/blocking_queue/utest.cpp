#include "mu_test.h"
#include "blocking_queue.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "mutex_exceptions.hpp"
#include "thread_exceptions.hpp"
#include <stdio.h>

mt::Mutex m;
int tVar1 = -1; // testing fifo between 0-50
int tVar2 = 49; // testing fifo between 51-100

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
    while (i < end)
    {
        queue->enqueue(i++);
    }

    return 0;
}

void *dequeueMany(void *a_arg)
{
    using namespace mt;
    int *arr = new int[100];
    BlockingQueue<int> *queue = static_cast<BlockingQueue<int> *>(a_arg);

    size_t i = 0;
    while (i < 100)
    {
        queue->dequeue(arr[i]);
        ++i;
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
BlockingQueue<int> q(100);
Arguments<int> queueArg(&q, 0, 100);

mt::Thread t1(0, enqueueMany, static_cast<void *>(&queueArg));

mt::Thread t2(0, dequeueMany, static_cast<void *>(&q));
t1.join();
void *res = t2.join();
int *y = static_cast<int *>(res);
for (size_t i = 0; i < 100; ++i)
{
    std::cout << y[i] <<",";
    ASSERT_EQUAL(y[i], (int)i);
}
ASSERT_EQUAL(q.isEmpty(), true);
END_TEST

BEGIN_TEST(fifo_test_two_thread_enque_one_dequeue)
using namespace mt;
BlockingQueue<int> q(100);
Arguments<int> first(&q, 0, 50);
Arguments<int> second(&q, 50, 100);

mt::Thread t1(0, enqueueMany, static_cast<void *>(&first));
mt::Thread t2(0, enqueueMany, static_cast<void *>(&second));

mt::Thread t3(0, dequeueMany, static_cast<void *>(&q));

t1.join();
t2.join();
void *res = t3.join();
int *y = static_cast<int *>(res);
for (size_t i = 0; i < 100; ++i)
{
    std::cout << y[i] <<",";
    ASSERT_EQUAL(ensureFIFO(y[i]), true);
}
ASSERT_EQUAL(q.isEmpty(), true);
END_TEST

BEGIN_SUITE(tests)
TEST(fifo_test_one_thread_enque_one_dequeue)
TEST(fifo_test_two_thread_enque_one_dequeue)

END_SUITE