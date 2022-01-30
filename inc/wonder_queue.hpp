#ifndef WONDER_QUEUE_H
#define WONDER_QUEUE_H

#include "stack.hpp"
#include <stddef.h>

static int const CAPACITY = 20;

class WonderQueue
{
public:
    WonderQueue(size_t _capacity = CAPACITY); 
    bool isFull() const;
    bool isEmpty() const;
    size_t size() const;
    void dump() const;
    size_t capacity();

    void enqueue(int item);
    size_t dequeue();

private:
    Stack m_dataOut;
    Stack m_dataIn;
    size_t m_actualCapacity;

private:
    void axioms() const;

};


#endif /*ifndef WONDER_QUEUE_H*/