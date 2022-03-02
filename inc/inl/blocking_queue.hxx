#ifndef BLOCKING_QUEUE_HXX
#define BLOCKING_QUEUE_HXX

namespace mt
{

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_elements(new T[a_capacity])
, m_capacity(a_capacity)
{
	m_list = cpp::LinkedList<T>();
}

template <typename T>
void BlockingQueue<T>::enqueue(T const& a_value)
{
	if(!m_mtx.isLock())
	{
		m_mtx.lock();
		m_list.addLast(a_value);
		m_mtx.unlock();
	}
}

template <typename T>
T BlockingQueue<T>::dequeue()
{
	T removed;
	if(!m_mtx.isLock())
	{
		m_mtx.lock();
		removed = m_list.remove();
		m_mtx.unlock();
	}

	return removed;
}


template <typename T>
void BlockingQueue<T>::print() const
{
	m_list.printList();
}

template <typename T>
bool BlockingQueue<T>::isEmpty() const
{
	return m_list.size() == 0;
}

template <typename T>
bool BlockingQueue<T>::isFull() const
{
	return m_list.size() == m_capacity;
}

template <typename T>
T BlockingQueue<T>::getFront() const
{
	return m_list.first();
}

template <typename T>
T BlockingQueue<T>::getBack() const
{
	return m_list.last();
}

template <typename T>
size_t BlockingQueue<T>::getCapacity() const
{
	return m_capacity;
}

template <typename T>
size_t BlockingQueue<T>::size() const
{
	return m_list.size();
}


}//namespace mt

#endif /*#ifndef BLOCKING_QUEUE_HXX*/