#include <cstdio>
#include <cassert>
#include <stdlib.h>

#include <cstring>
#include "../inc/stack.hpp"

// static const int MAGIC_NUM = 0xCDCDCDCD;

Stack::Stack(size_t a_capacity)
: m_tos(0)
, m_capacity(a_capacity)
, m_elements(new int [m_capacity])
{
    //+1 for sentinal
    // m_elements[_capacity] = MAGIC_NUM;
    axioms();
    printf("ctor of stack [%d]\n", (int)m_capacity);
}

Stack::~Stack()
{
    delete[] m_elements;
    printf("dtor of stack [%d]\n", (int)m_capacity);
}

// copy constructor
Stack::Stack(const Stack &a_stack)
: m_tos(a_stack.m_tos)
, m_capacity(a_stack.m_capacity)
, m_elements(new int[m_capacity])
{
    for(size_t i = 0; i < m_tos; i++)
    {
        m_elements[i] = a_stack.m_elements[i];
    }
}

// copy-assingnment operator
Stack& Stack::operator=(Stack const& a_stack)
{
    m_tos = a_stack.m_tos;
    m_capacity = a_stack.m_capacity;

    int* copy = new int[m_capacity];

    memcpy(copy, a_stack.m_elements, a_stack.m_capacity*sizeof(int));

    delete[] m_elements;
    m_elements = copy;

    return *this;
}

Stack::Stack(int const* a_array, size_t a_stackSize)
: m_tos(0)
, m_capacity(a_stackSize)
, m_elements(new int [m_capacity])
{
    assert(a_array != 0);
    pushArr(a_array, a_stackSize);
    printf("ctor of stack [%d]\n", (int)m_capacity);
}

Stack::Stack(int const* a_array, size_t a_stackSize, size_t a_formSize)
: m_tos(0)
, m_capacity(a_stackSize)
, m_elements(new int [m_capacity])
{
    assert(a_array != 0);
    assert(a_formSize >= 0);
    pushArr(a_array, a_formSize);
    printf("ctor of stack [%d]\n", (int)m_capacity);
}

void Stack::drain(Stack& a_source)
{
    ensureCapacity(a_source.capacity());
    while(a_source.m_tos != 0)
    {
        push(a_source.pop());
    }
        
    axioms();
}

void combineStacks(Stack& a_destination, Stack& a_firstStack, Stack& a_secondStack)
{
    size_t totalSize = a_firstStack.size() + a_secondStack.size();
    a_destination.ensureCapacity(totalSize);
    a_destination.drain(a_firstStack);
    a_destination.drain(a_secondStack);
}
//fail-fast assert: noisy fail
// return size_t how much wprk was done
size_t findMin(size_t a_first, size_t a_second)
{
    if(a_first >= a_second){
        return a_first;
    }
    else{
        return a_second;
    }
}

size_t Stack::pushArr(int const* a_array, size_t a_toPush)
{
    assert(a_array != 0);
    int pushed = findMin(a_toPush, m_capacity - m_tos);
    if(pushed > 0)
    {
        memcpy(m_elements + m_tos, a_array, pushed * sizeof(m_elements[0]));
        m_tos += pushed;
    }
    axioms();
    
    return pushed;
}

//bool find(int const* array, size_t len, int x, site_t* index)
// if not found - return false and insert to index the index num found

size_t Stack::popIntoArr(int* a_array, size_t a_toPop)
{
    size_t i = 0;
    for(; i < a_toPop && !isEmpty(); i++)
    {
        a_array[i] = pop();
    }
    axioms();
    
    return i;
}

bool Stack::isEmpty() const
{
    axioms();
    return m_tos == 0;
}

bool Stack::isFull() const
{
    axioms();
    return m_tos == m_capacity;
}

size_t Stack::size() const
{
    axioms();
    return m_tos;
}

size_t Stack::capacity() const
{
    axioms();
    return m_capacity;
}

int* Stack::elements() const
{
    axioms();
    return m_elements;
}

void Stack::ensureCapacity(size_t n)
{
    if(capacity() >= n){
        return;
    }
    int* copy = new int[n];
    memcpy(copy, m_elements, m_tos * sizeof(m_elements[0]));
    int* oldArr = m_elements;
    m_elements = copy;
    m_capacity = n;
    delete[] oldArr;
    axioms();
}

size_t Stack::top() const
{
    int t = m_elements[m_tos];
    
    return t;
}

size_t Stack::pop()
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
    for (size_t i = 0; i < m_tos; i++)
    {
        printf("%d ", m_elements[i]);
    }

    axioms();
}

void Stack::dump() const
{
    printf("tos: %d, cap: %d\n", (int)m_tos, (int)m_capacity);
    dumpElements();
    printf("\n");
}

void Stack::empty()
{
    m_tos = 0;
    axioms();
}

void Stack::axioms() const
{
    assert (m_capacity >= 0);
    assert (m_elements != 0);
    assert (0 <= m_tos && m_tos <= m_capacity);
}