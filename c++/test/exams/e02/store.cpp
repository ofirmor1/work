#include "store.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>

namespace cpp
{

Store::Store(size_t a_size)
: m_size()
, m_capacity(a_size)
, m_arr(new int[m_capacity])
{}

Store::~Store()
{
    delete[] m_arr;
}

Store::Store(Store const& a_source)
: m_size(a_source.m_size)
, m_capacity(a_source.m_capacity)
, m_arr(new int[a_source.m_capacity])
{
    memcpy(m_arr, a_source.m_arr, sizeof(a_source.m_size * a_source.m_arr[0]));
}

Store& Store::operator=(Store const& a_source)
{
    if (this != &a_source)
    {
        m_size = a_source.m_size;
        m_capacity = a_source.m_capacity;
        delete[] m_arr;
        m_arr = new int[a_source.m_capacity];
        std::copy(&a_source.m_arr[0], &a_source.m_arr[0] + m_size, &m_arr[0]);
    }

    return *this;
}

int Store::get(size_t a_indx) const
{
    return m_arr[a_indx];
}

void Store::set(size_t a_index, int a_value)
{
    m_arr[a_index] = a_value;
    ++m_size;
}

void Store::reset(int a_value)
{
    std::fill_n(m_arr, m_size, a_value);
}

void Store::print() const
{
    for (size_t i = 0; i < m_size; i++)
    {
        std::cout << m_arr[i] << std::endl;
    }
}

size_t Store::getSize() const
{
    return m_size;
}

size_t Store::getCapacity() const
{
    return m_capacity;
}

int Store::operator[](size_t a_index)
{
    return m_arr[a_index];
}

}//namespace cpp