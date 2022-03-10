#ifndef QUEUE_HXX
#define QUEUE_HXX

#include <cstddef>

namespace cpp
{
template <typename T>
Queue<T>::Queue(size_t a_capacity)
: m_elements(new T[a_capacity])
, m_capacity(a_capacity)
{
	m_list = LinkedList<T>();
}
 
template <typename T>
void Queue<T>::enqueue(T const& a_value)
{
	m_list.addLast(a_value);
}

template <typename T>
T Queue<T>::dequeue()
{
	return m_list.remove();
}


template <typename T>
void Queue<T>::print() const
{
	m_list.printList();
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	return m_list.size() == 0;
}

template <typename T>
bool Queue<T>::isFull() const
{
	return m_list.size() == m_capacity;
}

template <typename T>
T Queue<T>::getFront() const
{
	return m_list.first();
}

template <typename T>
T Queue<T>::getBack() const
{
	return m_list.last();
}

template <typename T>
size_t Queue<T>::capacity() const
{
	return m_capacity;
}

template <typename T>
size_t Queue<T>::size() const
{
	return m_list.size();
}

}//namespace cpp

#endif /*#ifndef QUEUE_HXX*/