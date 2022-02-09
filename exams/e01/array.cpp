#include "array.hpp"

ArrayOfInt::ArrayOfInt()
: m_isFull(0)
{}

ArrayOfInt::ArrayOfInt(int* a_array, size_t a_size)
{

}

bool ArrayOfInt::isFull() const
{
    return m_isFull == 1;
}

bool ArrayOfInt::isEmpty() const
{
    return m_size == 0;
}

void ArrayOfInt::print() const
{

}
