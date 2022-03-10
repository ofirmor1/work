#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stddef.h>
#include <cassert>
#include "single_list.hpp"

namespace cpp
{
template <typename T>
class Queue
{
public:
	static const size_t CAPACITY = 16;
    Queue(size_t a_capacity = CAPACITY);

	void enqueue(T const& a_value);
	T dequeue();

    bool isEmpty() const;
    bool isFull() const;
	void print() const;
	size_t size() const;
	size_t capacity() const;

	T getFront() const;
	T getBack() const;
	

private:
    Queue(Queue const& a_queue);
	Queue& operator=(Queue const& a_queue);
	void clear();

private:
	LinkedList<T> m_list;
	T* m_elements;
	size_t m_capacity;
};

}//namespace cpp

#include "./inl/queue.hxx"

#endif /*#ifndef QUEUE_HPP*/
