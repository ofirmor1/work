#include<iostream>
#include<cassert>

#include "array.hpp"


ArrayOfInt::ArrayOfInt(size_t a_size)
: m_isFull(0)
, m_size(a_size)
, m_array(new int [m_size])
{}
ArrayOfInt::~ArrayOfInt()
{}

bool ArrayOfInt::isFull() const
{
    return m_isFull == 1;
}

bool ArrayOfInt::isEmpty() const
{
    return m_size == 0;
}

std::ostream& ArrayOfInt::print(std::ostream& os) const
{
    for (int i = 0; i < m_size; i++)
    {
        os << "element [i]: " << m_array[i] << '\n';
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, Rational const& a_array)
{
 return a_array.print(os);
}

void ArrayOfInt::axioms()
{
    assert(m_size > 0);
}
