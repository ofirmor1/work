#include <cstdio>
#include <cassert>
#include <stdlib.h>

#include "min_stack.hpp"
#include "stack.hpp"

MinStack::MinStack(size_t a_cap)
: m_data(a_cap)
, m_min(a_cap)
{
    
}

void MinStack::push(int a_data)
{
    assert(m_data.isFull() == false);
    if(m_data.isEmpty())
    {
        m_min.push(a_data); 
    }
    m_data.push(a_data);
    if(a_data < (int)m_min.top())
    {
        m_min.push(a_data);
    } 
}

int MinStack::pop()
{
    assert(m_data.isEmpty() == false);
    int r;
    if(m_data.top() == m_min.top())
    {
        r = m_data.pop();
        m_min.pop();
    }
    else
    {
        r = m_data.pop();
    }

    return r;
}

int MinStack::top() const
{
    assert(m_data.isEmpty() == false);

    return m_data.top();
}

int MinStack::minVal() const
{
    assert(m_data.isEmpty() == false);
    int r = m_min.top();

    return r;
}


bool MinStack::isEmpty() const
{
    return m_data.isEmpty();
}

bool MinStack::isFull() const
{   
    return m_data.isFull();
}
