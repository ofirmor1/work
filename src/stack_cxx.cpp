#include <cstdio>
#include <cassert>
#include <stdlib.h>
#include "../inc/stack.hpp"

// static const int MAGIC_NUM = 0xCDCDCDCD;

Stack::Stack(int a_capacity)
: m_tos(0)
, m_capacity(a_capacity)
, m_elements(new int [m_capacity])
{
    //+1 for sentinal
    // m_elements[_capacity] = MAGIC_NUM;
    axioms();
    printf("ctor of stack [%u]\n", m_capacity);
}

Stack::Stack(const Stack &a_stack)
{
    m_tos = a_stack.m_tos;
    m_capacity = a_stack.m_capacity;
    m_elements = new int[m_capacity];
    for(int i = 0; i < m_tos; i++)
    {
        m_elements[i] = a_stack.m_elements[i];
    }
}

Stack::Stack(int* a_array, int a_arrSize)
: m_tos(0)
, m_capacity(10)
, m_elements(new int [m_capacity])
{
    axioms();
    assert(a_array != 0);
    pushArr(a_array, a_arrSize);
    printf("ctor of stack [%u]\n", m_capacity);
}

Stack::Stack(int* a_array, int a_arrSize, int a_formSize)
: m_tos(0)
, m_capacity(128)
, m_elements(new int [m_capacity])
{
    axioms();
    assert(a_array != 0);
    assert(a_formSize >= 0);
    pushArr(a_array, a_arrSize);
    printf("ctor of stack [%u]\n", m_capacity);
}

Stack combineStacks(Stack a, Stack b)
{
    Stack stack;
    while(!a.isEmpty())
    {
        stack.push(a.pop());
    }
    while(!b.isEmpty())
    {
        stack.push(b.pop());
    }

    return stack;
}

void Stack::pushArr(int* a_array, int a_arrSize)
{
    int i = 0;
    while(i < a_arrSize && !isFull())
    {
        push(a_array[i++]);
    }

    axioms();
}

void Stack::popIntoArr(int* a_array, int a_arrSize)
{
    int i = 0;
    while(i < a_arrSize  && !isEmpty())
    {
        a_array[i++] = pop();
    }

    axioms();
}

Stack::~Stack()
{
    delete[] m_elements;
    printf("dtor of stack [%u]\n", m_capacity);
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