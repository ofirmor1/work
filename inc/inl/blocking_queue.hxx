#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <utility>

namespace mt
{
template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_queue()
, m_mtx()
{}

template <typename T>
bool BlockingQueue<T>::enqueue(T const& a_value)
{
	try
	{
		m_mtx.lock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}
	
	if(nonLockFull())
	{
		m_mtx.unlock();
		return false;
	}

	m_queue.enqueue(a_value);
	
	try
	{
		m_mtx.unlock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}
	
	return true;
}

template <typename T>
T BlockingQueue<T>::dequeue(bool& ok)
{
	try
	{
		m_mtx.lock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}
    
	if(nonLockEmpty())
	{
		ok = false;
		m_mtx.unlock();
		return 0;
	}
	
	T res = m_queue.dequeue();
	ok = true;

	try
	{
		m_mtx.unlock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}

	return res;
}

template <typename T>
void BlockingQueue<T>::print() const
{
	m_mtx.lock();
	m_queue.printList();
	m_mtx.unlock();
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
	m_mtx.lock();
	bool r = m_queue.size() == 0;
	m_mtx.unlock();

	return r;
}

template <typename T>
bool BlockingQueue<T>::nonLockEmpty() const
{
	return m_queue.isEmpty();
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
	m_mtx.lock();
	bool r = (m_queue.size() == m_queue.cap());
	m_mtx.unlock();

	return r;
}

template <typename T>
bool BlockingQueue<T>::nonLockFull() const
{
	return m_queue.isFull();
}

template <typename T>
T BlockingQueue<T>::getFront() const
{
	m_mtx.lock();
	T r = m_queue.first();
	m_mtx.unlock();

	return r;
}

template <typename T>
T BlockingQueue<T>::getBack() const
{
	m_mtx.lock();
	T r = m_queue.last();
	m_mtx.unlock();

	return r;
}

template <typename T>
size_t BlockingQueue<T>::getCapacity() const
{
	return	m_queue.cap();
}

template <typename T>
size_t BlockingQueue<T>::size() const
{
	m_mtx.lock();
	size_t size = m_queue.size(); 
	m_mtx.unlock();

	return size;
}


}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/