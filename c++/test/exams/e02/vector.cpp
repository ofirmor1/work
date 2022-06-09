#include "vector.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace cpp
{

Vector::Vector(size_t a_size)
: m_vec(a_size)
{}

int Vector::sumElements(size_t a_from, size_t a_to) const
{
    return std::accumulate(m_vec.begin() + a_from, m_vec.end(), 0);
} 

void Vector::Update(size_t a_index, int a_value)
{
    m_vec[a_index] = a_value;
}

void Vector::insert(int a_value)
{
    m_vec.push_back(a_value);
}

size_t Vector::getSize() const
{
    return m_vec.size();
}

int Vector::operator[](size_t a_index)
{
    return m_vec[a_index];
}

}//namespace cpp