#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

#include <utility>
#include "mutex_exceptions.hpp"
#include "blocking_queue_exceptions.hpp"

namespace mt
{
template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
try: m_queue(a_capacity)
, m_mtx()
{}
catch(const std::exception& e)
{
	std::cerr << e.what() << '\n';
}


template <typename T>
void BlockingQueue<T>::enqueue(T const& a_value)
{
	lockQueue();

		if (nonLockFull())
		{
			unLockQueue();
			throw BlockingQueueIsFull();
		}
		m_queue.enqueue(a_value);
}

template <typename T>
void BlockingQueue<T>::dequeue(T& a_retVal)
{
	lockQueue();

		if (nonLockEmpty())
		{
			unLockQueue();
			throw BlockingQueueIsEmpty();
		}
		a_retVal = m_queue.dequeue();
		unLockQueue();

}

template <typename T>
void BlockingQueue<T>::print() const
{
	lockQueue();
	m_queue.printList();
	unLockQueue();
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
	lockQueue();
	bool ret = m_queue.isEmpty();
	unLockQueue();
	return ret;
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
	lockQueue();
	if(m_queue.capacity())
	{
		unLockQueue();
		return m_queue.size() == m_queue.capacity();
	}
	unLockQueue();
	return false;
}

template <typename T>
bool BlockingQueue<T>::nonLockEmpty() const
{
	return m_queue.isEmpty();
}

template <typename T>
bool BlockingQueue<T>::nonLockFull() const
{
	if(m_queue.capacity())
	{
		return m_queue.isFull();
	}

	return false;
}

template <typename T>
void BlockingQueue<T>::lockQueue() const
{
	try
	{
		m_mtx.lock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}
}

template <typename T>
void BlockingQueue<T>::unLockQueue() const
{
	try
	{
		m_mtx.unlock();
	}
	catch(const std::exception& e)
	{
		assert(!e.what());
	}
}

template <typename T>
T BlockingQueue<T>::getFront() const
{
	lockQueue();
	try
	{
		if(!m_queue.isEmpty())
		{
			return m_queue.getFront();
		}
	}
	catch(const std::exception& e)
	{
		throw;
	}	
}

template <typename T>
T BlockingQueue<T>::getBack() const
{
	lockQueue();
	try
	{
		if(!m_queue.isEmpty())
		{
			return m_queue.getBack();
		}
	}
	catch(const std::exception& e)
	{
		throw;
	}	
}

template <typename T>
size_t BlockingQueue<T>::getCapacity() const
{
	return	m_queue.cap();
}

template <typename T>
size_t BlockingQueue<T>::size() const
{
	lockQueue();
	try
	{
		if(m_queue)
		{
			return m_queue.size();
		}
	}
	catch(const std::exception& e)
	{
		throw;
	}
}

template <typename T>
void BlockingQueue<T>::clear()
{
	lockQueue();
	try
	{
		m_queue.clear();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}


}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/