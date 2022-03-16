#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include "thread.hpp"

namespace mt
{

template<typename F>
struct ThreadPool
{
    ThreadPool(std::vector<F>& a_vec);
    void join();

private:
    ThreadPool& operator=(ThreadPool const& a_pool);

private:
    std::vector<Thread> m_threads;
};

} // namespace mt

#include "./inl/thread_pool.hxx"

#endif /* THREAD_POOL_HPP */