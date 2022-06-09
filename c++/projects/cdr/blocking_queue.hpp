#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <iostream>
#include <stddef.h>
#include <cassert>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace mt
{
template <typename T>
class BlockingQueue
{
public:
	static const size_t CAPACITY = 16;

    BlockingQueue(size_t a_capacity = CAPACITY);
	~BlockingQueue() = default;

	void enqueue(T const& a_value);
	T& dequeue();
	void clear();

    bool isEmpty() const;
    bool isFull() const;

	void print() const;
	size_t size() const;
	size_t getCapacity() const;

	T getFront() const;
	T getBack() const;

	void lockQueue() const;
	void unLockQueue() const;

	T const& operator[](size_t a_index) const;

private:
	bool nonLockEmpty() const;
	bool nonLockFull() const;
    BlockingQueue(BlockingQueue const& a_source);//no imp by design
	BlockingQueue& operator=(BlockingQueue const& a_source);//no imp by design

private:
	std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    size_t m_capacity;
};


}//namespace mt

#include "blocking_queue.hxx"

#endif /*#ifndef BLOCKING_QUEUE_HPP*/