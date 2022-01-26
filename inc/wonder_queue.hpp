#ifndef WONDER_QUEUE_H
#define WONDER_QUEUE_H

#include "stack.hpp"

class WonderQueue
{
public:
WonderQueue(size_t _size); 
bool isFull() const;
bool isEmpty() const;
size_t capacity() const;
size_t size() const;
void dump(WonderQueue a_que) const;

void enqueue(int item);
int dequeue();

private:
Stack m_stack;
size_t m_capacity;
size_t m_size;

private:
void axioms() const;


};


#endif /*ifndef WONDER_QUEUE_H*/