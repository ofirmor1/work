#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <iostream>
#include <stddef.h>
#include <cassert>
#include "single_list.hpp"
#include "mutex.hpp"

const size_t CAPACITY = 10;

namespace mt
{

template <typename T>
class BlockingQueue
{
public:
    BlockingQueue(size_t a_capacity = CAPACITY);

	void enqueue(T const& a_value);
	T dequeue();

    bool isEmpty() const;
    bool isFull() const;
	void print() const;
	size_t size() const;
	size_t cap() const;

	T getFront() const;
	T getBack() const;
	size_t getCapacity() const;

private:
    void copy(BlockingQueue const& a_queue);
	void clear();

private:
	cpp::LinkedList<T> m_list;
	T* m_elements;
	size_t m_capacity;
	Mutex m_mtx;
};


}//namespace mt

#include "./inl/blocking_queue.hxx"

#endif /*#ifndef BLOCKING_QUEUE_HPP*/