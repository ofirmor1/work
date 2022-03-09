#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <iostream>
#include <stddef.h>
#include <cassert>
#include "queue.hpp"
#include "mutex.hpp"

namespace mt
{
template <typename T>
class BlockingQueue
{
public:
	static const size_t CAPACITY = 16;

    BlockingQueue(size_t a_capacity = CAPACITY);

	bool enqueue(T const& a_value);
	T dequeue(bool& ok);
	void clear();

    bool isEmpty() const;
    bool isFull() const;

	void print() const;
	size_t size() const;
	size_t getCapacity() const;

	T getFront() const;
	T getBack() const;

private:
	bool nonLockEmpty() const;
	bool nonLockFull() const;
    BlockingQueue(BlockingQueue const& a_source);//no imp by design
	BlockingQueue& operator=(BlockingQueue const& a_source);//no imp by design

private:
	cpp::Queue<T> m_queue;
	mutable Mutex m_mtx;
};


}//namespace mt

#include "./inl/blocking_queue.hxx"

#endif /*#ifndef BLOCKING_QUEUE_HPP*/