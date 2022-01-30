#include "mu_test.h"
#include "wonder_queue.hpp"

BEGIN_TEST(que_push_pop_size_capacity_isFull_isEmpty)
	WonderQueue que(10);

    for(int i = 1; i <= 5; i++)
    {
        que.enqueue(i);
    }

    ASSERT_EQUAL(que.size(), 5);
    ASSERT_EQUAL(que.capacity(), 20);
    ASSERT_THAT(!que.isFull());

    for(int i = 6; i <= 10; i++)
    {
        que.enqueue(i);
    }

    ASSERT_THAT(!que.isFull());

    for(int i = 11; i <= 20; i++)
    {
        que.enqueue(i);
    }

    ASSERT_EQUAL(que.size(), 20);
    ASSERT_THAT(que.isFull());

    for(int i = 1; i <= 20; i++)
    {
        que.dequeue();
    }

    ASSERT_THAT(que.isEmpty());
       
END_TEST

BEGIN_SUITE(queue_run_tests)
	TEST(que_push_pop_size_capacity_isFull_isEmpty)
END_SUITE