#include <cstdio>
#include <cassert>
#include <stdlib.h>
#include <cstring>
#include "wonder_queue.hpp"
#include "stack.hpp"

WonderQueue::WonderQueue(size_t a_capacity)
: m_dataOut(a_capacity)
, m_dataIn(a_capacity)
, m_actualCapacity(a_capacity)
{
    axioms();
    printf("ctor of queue [%d]\n", (int)m_actualCapacity);
}

void WonderQueue::enqueue(int item)
{
    if(!m_dataOut.isFull())
    {
        m_dataOut.push(item);
    }
    else
    {
        while(!(m_dataIn.isFull()))
        {
            m_dataIn.push(m_dataOut.pop());
        }
        m_dataOut.push(item);
    }
    axioms();
}

size_t WonderQueue::dequeue()   
{
    size_t r;
    if (m_dataIn.size() > 0)
    {
       r = m_dataIn.pop();
    }
    else
    {
        m_dataIn.drain(m_dataOut);
        r = m_dataIn.pop();
    }
    axioms();
    return r;
}

size_t WonderQueue::capacity()
{
    if(m_dataOut.isEmpty() || m_dataOut.isFull())
    {
        m_actualCapacity = m_dataIn.capacity() + m_dataOut.capacity();
    }
    else
    {
        m_actualCapacity = m_dataIn.capacity() + m_dataOut.capacity();
    }

    return m_actualCapacity;
}

size_t WonderQueue::size() const
{
    return m_dataOut.size() + m_dataIn.size();
}

bool WonderQueue::isFull() const
{
    return m_actualCapacity == m_dataIn.size() + m_dataOut.size();
}

bool WonderQueue::isEmpty() const
{
    return m_dataOut.isEmpty() && m_dataIn.isEmpty();
}

void WonderQueue::dump() const
{
    m_dataOut.dump();
    m_dataIn.dump();
}

void WonderQueue::axioms() const
{
    assert(m_actualCapacity >= m_dataIn.capacity());
    assert(m_actualCapacity <= m_dataIn.capacity() + m_dataOut.capacity());
}