#ifndef THREAD_POOL_HXX
#define THREAD_POOL_HXX

namespace mt
{

template<typename F>
ThreadPool<F>::ThreadPool(std::vector<F>& a_vec)
:m_threads()
{
    m_threads.reserve(a_vec.size() );
    size_t const size = a_vec.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_threads.push_back(a_vec[i]);
    }
}

template<typename F>
void mt::ThreadPool<F>::join()
{
    size_t const size = m_threads.size();
    for(size_t i = 0; i < size; ++i)
    {
        m_threads[i].join();
    }
}

}// namespace mt


#endif /* THREAD_POOL_HXX */