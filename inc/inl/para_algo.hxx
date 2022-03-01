#ifndef PARA_ALGO_HXX
#define PARA_ALGO_HXX

#include "para_algo.hpp"
#include <pthread.h>
#include <vector>
#include <cstddef>
#include <stddef.h>
#include <numeric>
#include <iostream>
#include <stdio.h>
#include <algorithm>

namespace cpp
{

struct Args
{
    Args(std::vector<int> const& a_vec, size_t a_from, size_t a_to)
    : m_vec(a_vec)
    , m_from(a_from)
    , m_to(a_to)
    {}

    std::vector<int> const& m_vec;
    size_t m_from;
    size_t m_to;
    
};

void* sumSection(void* a_arg)
{
    if(!a_arg)
    {
        return 0;
    }

    Args* arg = static_cast<Args*>(a_arg);
    
    int* sum =  new int;;
    for(size_t i = arg->m_from; i < arg->m_to; ++i)
    {
        *sum += arg->m_vec[i];
    }
    
    return sum;
}

size_t sumVector(std::vector<int> const& a_vec, size_t a_numOfThreads)
{
    size_t globalSum = 0;
    size_t section = a_vec.size() / a_numOfThreads;
    size_t from = 0;
    size_t to = section;

    for (size_t i = 0; i < a_numOfThreads; ++i)
    {
        pthread_t th;
        void* partialSum;

        Args* args = new Args(a_vec, from, to);

        if(::pthread_create(&th, 0, sumSection, static_cast<void*>(args)) != 0)
        {
            perror("Failed to create thread");
        }

        if(::pthread_join(th, &partialSum) != 0)
        {
            perror("Failed to join thread");
        }

        globalSum += *static_cast<size_t*>(partialSum);
        from = to;
        to += section;
    }

    return globalSum;
}

void* sortSection(void* a_arg)
{
    if(!a_arg)
    {   
        return 0;
    }  

    Args* arg = static_cast<Args*>(a_arg);
    
    // std::sort (arg->m_vec.begin(), arg->m_vec.end());

    return static_cast<void*>(arg);
}


}//namespace cpp

#endif /*#ifndef PARA_ALGO_HXX*/