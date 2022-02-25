#ifndef SORTED_UNIQUE_VECTOR_HXX
#define SORTED_UNIQUE_VECTOR_HXX

#include <vector>
#include "my_iterator.hpp"

namespace cpp
{

template <typename T>
void SortedUniqueVector<T>::insert(T a_val)
{
    m_elements.insert(a_val);
    // Itr last = std::unique(m_elements.begin(), m_elements.end());
    // m_elements.erase(last, m_elements.end());
// std::unique(v.begin(), v.end());

}
template <typename T>
size_t SortedUniqueVector<T>::contains(T a_val) const
{
    return m_elements.contains(a_val);
}

template <typename T>
size_t SortedUniqueVector<T>::remove(T a_val)
{
    return m_elements.remove(a_val);
}

template <typename T>
T SortedUniqueVector<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T SortedUniqueVector<T>::back() const
{
    return m_elements.back();
}

template <typename T>
MyIterator<T> SortedUniqueVector<T>::begin()
{
    return m_elements.begin();
}

template <typename T>
MyIterator<T> SortedUniqueVector<T>::end()
{
    return m_elements.end();
}

template <typename T>
std::ostream& SortedUniqueVector<T>::print(std::ostream& a_os) const
{
    return m_elements.print(a_os);
}

template <typename T>
size_t SortedUniqueVector<T>::size() const
{
    return m_elements.size();
}

template <typename T>
void SortedUniqueVector<T>::fill(T a_elem, size_t a_times)
{
    m_elements.fill(a_elem, a_times);
}

// template <typename T>
// T SortedUniqueVector<T>::median() const;

// template <typename T>
// bool SortedUniqueVector<T>::isSorted() const;

// template <typename T>
// bool SortedUniqueVector<T>::isUniform() const;

}// namespace cpp

#endif /*#ifndef SORTED_UNIQUE_VECTOR_HXX*/