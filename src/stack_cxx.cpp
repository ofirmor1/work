#include <cstdio>
#include <cassert>
#include <stdlib.h>
#include "../inc/stack.hpp"

Stack::Stack(int _capacity)
: m_tos(0)
, m_capacity(_capacity)
{
    m_elements = new int[_capacity];
    assert(!(m_elements == NULL));
 
}

Stack::~Stack()
{
    delete[] m_elements;
}

bool Stack::isEmpty() const
{
    return m_tos == 0;
}

bool Stack::isFull() const
{
    return m_tos == m_capacity;
}

int Stack::size() const
{
    return m_tos;
}

int Stack::pop()
{
    assert(!isEmpty());
    int r = m_elements[--m_tos];
    axioms();

    return r;
}

void Stack::push(int value)
{
    assert(!isFull());
    m_elements[m_tos++] = value;

    axioms();
}

void Stack::dumpElements() const
{
    for (int i = 0; i < m_tos; i++)
    {
        printf("%d ", m_elements[i]);
    }

    axioms();
}

void Stack::dump() const
{
    printf("tos: %d, cap: %d\n", m_tos, m_capacity);
    dumpElements();
    printf("\n");
}

void Stack::empty()
{
    while(m_tos >= 0)
    {
        pop();
    }

    axioms();
}

void Stack::axioms() const
{
    assert (m_capacity >= 0);
    assert (m_elements != 0);
    assert (0 <= m_tos && m_tos <= m_capacity);
}