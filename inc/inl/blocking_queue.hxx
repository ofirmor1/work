#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <utility>
#include "multi_thread_utils.hpp"
#include "mutex_exceptions.hpp"
#include "blocking_queue_exceptions.hpp"

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
	ResourceGuard<mt::Mutex, BlockingQueueIsEmpty> guard(m_mtx);

	if (nonLockFull())
	{
		throw BlockingQueueIsFull();
	}
	m_queue.enqueue(a_value);
}

template <typename T>
void BlockingQueue<T>::dequeue(T& a_retVal)
{
	ResourceGuard<mt::Mutex, BlockingQueueIsEmpty> guard(m_mtx);

	if (nonLockEmpty())
	{
		unLockQueue();
		throw BlockingQueueIsEmpty();
	}
	a_retVal = m_queue.dequeue();
}

template <typename T>
void BlockingQueue<T>::print() const
{
	ResourceGuard<mt::Mutex, BlockingQueueExceptions> guard(m_mtx);
	m_queue.printList();
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
	ResourceGuard<mt::Mutex, BlockingQueueIsEmpty> guard(m_mtx);

	bool ret = m_queue.isEmpty();
	return ret;
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
	ResourceGuard<mt::Mutex, BlockingQueueIsFull> guard(m_mtx);

	bool ret = m_queue.isFull();
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
	ResourceGuard<mt::Mutex, BlockingQueueExceptions> guard(m_mtx);

	return m_queue.size();
}

template <typename T>
void BlockingQueue<T>::clear()
{
	ResourceGuard<mt::Mutex, BlockingQueueExceptions> guard(m_mtx);

	m_queue.clear();
}

}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/