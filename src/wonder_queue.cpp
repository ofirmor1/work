#include <cstdio>
#include <cassert>
#include <stdlib.h>
#include <cstring>
#include "wonder_queue.hpp"
#include "stack.hpp"

WonderQueue::WonderQueue(size_t a_capacity)
: m_stack(Stack(a_capacity))
, m_capacity(a_capacity)
, m_size(0)
{
    axioms();
    printf("ctor of queue [%d]\n", (int)m_capacity);
}

void WonderQueue::enqueue(int item)
{
        m_stack.push(item);
        m_size++;
}

int WonderQueue::dequeue()
{
    m_size--;
    return m_stack.pop();
}
size_t WonderQueue::capacity() const
{
    return m_stack.capacity();
}

size_t WonderQueue::size() const
{
    return m_stack.size();
}

bool WonderQueue::isFull() const
{
    return m_size == m_capacity;
}

bool WonderQueue::isEmpty() const
{
    return m_size == 0;
}

void WonderQueue::dump(WonderQueue a_que) const
{
    while(!isEmpty())
    {
        printf("%d ", a_que.dequeue());
    }
}


void WonderQueue::axioms() const
{
    assert(m_capacity >= 0);
    assert(m_capacity >= m_size);
    /*assert(m_stack != 0);*/
}
