#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <utility>
#include "../multi_thread_utils.hpp"
#include "../mutex_exceptions.hpp"
#include "../blocking_queue_exceptions.hpp"

namespace mt
{

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
try: m_queue(a_capacity)
, m_mtx()
{}
catch(mt::BlockingQueueExceptions const& fail)
{
	std::cerr << fail.what() << '\n';
}

template <typename T>
void BlockingQueue<T>::enqueue(T const& a_value)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while(nonLockFull())
	{
        m_cond.wait(lock);
    }
    m_queue.enqueue(a_value);
    lock.unlock();
	m_cond.notify_all();
}

template <typename T>
void BlockingQueue<T>::dequeue(T& a_retVal)
{
	std::unique_lock<std::mutex> lock(m_mtx);
    while(nonLockEmpty())
	{
        m_cond.wait(lock);
    }
    a_retVal = m_queue.dequeue();
    lock.unlock();
    m_cond.notify_all();
}

template <typename T>
void BlockingQueue<T>::print() const
{
	std::unique_lock<std::mutex> lock(m_mtx);
	m_queue.print();
	lock.unlock();
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
	std::unique_lock<std::mutex> lock(m_mtx);

	bool ret = m_queue.isEmpty();

	lock.unlock();
	return ret;
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
	std::unique_lock<std::mutex> lock(m_mtx);

	bool ret = m_queue.isFull();

	lock.unlock();
	return ret;
}

template <typename T>
bool BlockingQueue<T>::nonLockEmpty() const
{
	return m_queue.isEmpty();
}

template <typename T>
bool BlockingQueue<T>::nonLockFull() const
{
	return m_queue.isFull();
}

template <typename T>
size_t BlockingQueue<T>::getCapacity() const
{
	return m_queue.capacity();
}

template <typename T>
size_t BlockingQueue<T>::size() const
{
	std::unique_lock<std::mutex> lock(m_mtx);

	return m_queue.size();

	lock.unlock();
}

template <typename T>
void BlockingQueue<T>::clear()
{
	std::unique_lock<std::mutex> lock(m_mtx);
	m_queue.clear();
	lock.unlock();
}

}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/