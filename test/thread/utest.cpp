#include "mu_test.h"
#include "thread.hpp"
#include "mutex.hpp"

#include <iostream>

const size_t arrSize = 1000;
const size_t N = 1000 * 1000 * 10;
int arr[arrSize];
int g = 0;
int sum = 0;

mt::Mutex mtx;

void* incGlobalWithMutex(void*)
{
    for (size_t i = 0; i < N; ++i)
    {
        mtx.lock();
        ++g;
        mtx.unlock();
    }

    return 0;
}

void* incGlobalWithoutMutex(void*)
{
    for (size_t i = 0; i < N; ++i)
    {
        ++g;
    }

    return 0;
}

void* FillOdd(void*) {
    for(size_t i = 1; i < arrSize; i += 2) {
        arr[i] = i;
        std::cout << arr[i] << std::endl;
    }
    std::cout << "FILL ARRAY WITH ODD HAS FINISHED" << std::endl;

    return 0;
}

void* FillEven(void*) {
    for(size_t i = 0; i < arrSize; i += 2) {
        arr[i] = i;
        std::cout << arr[i] << std::endl;
    }
    std::cout << "FILL ARRAY WITH EVEN HAS FINISHED\n\n" << std::endl;

    return 0;
}

BEGIN_TEST(fill_array)
    mt::Thread th1(FillEven);
    mt::Thread th2(FillOdd);  
    th1.join();  
    th2.join();

    ASSERT_PASS();
    
END_TEST


BEGIN_TEST(inc_with_mutex)
	g = 0;
    mt::Thread t1(incGlobalWithMutex); 
    mt::Thread t2(incGlobalWithMutex);

    t1.join();
    t2.join();

    std::cout << "g = " << g << std::endl;
    ASSERT_EQUAL(g, N * 2);

END_TEST


BEGIN_TEST(inc_without_mutex)
	g = 0;
    mt::Thread t1(incGlobalWithoutMutex); 
    mt::Thread t2(incGlobalWithoutMutex);

    t1.join();
    t2.join();
    t2.join();

    std::cout << "g = " << g << std::endl;
    ASSERT_NOT_EQUAL(g, N * 2);

END_TEST


BEGIN_SUITE(tread_and_mutex_tests)
    TEST(fill_array)
    TEST(inc_with_mutex)
    TEST(inc_without_mutex)

END_SUITE
