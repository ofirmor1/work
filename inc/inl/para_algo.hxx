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
#include <cassert>

namespace cpp
{

template <typename T>
struct Args
{
    Args(std::vector<T> const& a_vec, size_t a_from, size_t a_to)
    : m_vec(a_vec)
    , m_from(a_from)
    , m_to(a_to)
    {}

    std::vector<T> const& m_vec;
    size_t m_from;
    size_t m_to;
    
};

template <typename T>
void* sumSection(void* a_arg)
{
    assert(a_arg);

    Args<T>* arg = static_cast<Args<T>* >(a_arg);
    size_t from = arg->m_from;
    size_t to = arg->m_to;
    std::vector<T> v = arg->m_vec;
    T sum = 0;
    while(from < to)
    {
        sum += v[from++];
    }
    T* ret =  new T(sum);

    return ret;
}

template <typename T>
size_t sumVector(std::vector<T> const& a_vec, size_t a_numOfThreads)
{
    size_t globalSum = 0;
    size_t section = a_vec.size() / a_numOfThreads;
    size_t from = 0;
    size_t to = section;

    std::vector<pthread_t> th (a_numOfThreads);
    
    for (size_t i = 0; i < a_numOfThreads; ++i)
    {
        void* partialSum;
        Args<T>* args = new Args<T>(a_vec, from, to);

        assert(::pthread_create(&th[i], 0, sumSection<T>, static_cast<void*>(args)) == 0);
        assert(::pthread_join(th[i], &partialSum) == 0);
        globalSum += *static_cast<size_t*>(partialSum);
        from = to;
        to += section;
    }

    return globalSum;
}

// template <typename T>
// void* sortSection(void* a_arg)
// {
//     assert(!a_arg);
//     Args<T>* arg = static_cast<Args<T>* >(a_arg);
//     typename std::vector<T>::iterator from = arg->m_vec.begin() + arg->m_from;
//     typename std::vector<T>::iterator to = arg->m_vec.begin() + arg->m_to;
//     std::sort (from, to);

//     return 0;
// }

// template <typename T>
// void* sortVector(std::vector<T>& a_vec, size_t a_numOfThreads)
// {
//     size_t const section = a_vec.size() / a_numOfThreads;
//     size_t from = 0;
//     size_t to = section;
//     for (size_t i = 0; i < a_numOfThreads; ++i)
//     {
//         Args<T>* arg = new Args<T> (a_vec, from, to);
//         pthread_t th;
//         ::pthread_create(&th, 0, sortSection<T>, static_cast<void*>(arg));
//         ::pthread_join(th, 0);
//         from = to;
//     }

//     return 0;
// }


}//namespace cpp

#endif /*#ifndef PARA_ALGO_HXX*/