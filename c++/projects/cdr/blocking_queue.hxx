#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <queue>
#include <mutex>
#include <condition_variable>
#include "blocking_queue_exceptions.hpp"

namespace mt
{

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
try: m_queue()
, m_mutex()
, m_capacity(a_capacity)
{}
catch(mt::BlockingQueueExceptions const& fail)
{
	std::cerr << fail.what() << '\n';
}

template <typename T>
void BlockingQueue<T>::enqueue(T const& a_data)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.size() == m_capacity)
	{
        m_cond.wait(lock);
    }
    m_queue.push(a_data);
    lock.unlock();
    m_cond.notify_all();
}

template <typename T>
T& BlockingQueue<T>::dequeue()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.empty())
    {
        m_cond.wait(lock);
    }
    T& returnData = m_queue.front();
    m_queue.pop();
    lock.unlock();
    m_cond.notify_all();

    return returnData;
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
    return m_queue.empty();
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
    return m_queue.full();
}

template <typename T>
T BlockingQueue<T>::getFront() const
{
    return m_queue.back();
}

template <typename T>
T BlockingQueue<T>::getBack() const
{
	return m_queue.front();
}

template <typename T>
size_t BlockingQueue<T>::size() const
{
    return m_queue.size();
}

template <typename T>
T const& BlockingQueue<T>::operator[](size_t a_index) const
{
    return m_queue[a_index];
}

}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/