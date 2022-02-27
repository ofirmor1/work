#ifndef SORTED_UNIQUE_VECTOR_HXX
#define SORTED_UNIQUE_VECTOR_HXX

#include <vector>
#include "my_iterator.hpp"

namespace cpp
{

template <typename T>
void SortedUniqueVector<T>::insert(T a_element)
{
    if(m_elements.empty())
    {
        m_elements.insert(a_element);
    }
    MyIterator<T> it = m_elements.begin();
    MyIterator<T> end = m_elements.end();

    while (it != end && *it < a_element)
    {   
        it++;
    }

    if(!(*it == a_element))
    {
        m_elements.insert(a_element);
    }
        
    // return m_elements.insert(a_element);
    // Itr last = std::unique(m_elements.begin(), m_elements.end()); ???????????????
    // m_elements.erase(last, m_elements.end());
}

template <typename T>
size_t SortedUniqueVector<T>::contains(T a_element) const
{
    return m_elements.contains(a_element);
}

template <typename T>
size_t SortedUniqueVector<T>::remove(T a_element)
{
    return m_elements.remove(a_element);
}

template <typename T>
T const& SortedUniqueVector<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T const& SortedUniqueVector<T>::back() const
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
void SortedUniqueVector<T>::fill(T a_element, size_t a_times)
{
    m_elements.fill(a_element, a_times);
}

template <typename T>
T SortedUniqueVector<T>::median() const
{
    return m_elements.median();
}

template <typename T>
bool SortedUniqueVector<T>::isSorted() const
{
    return m_elements.isSorted();
}

template <typename T>
bool SortedUniqueVector<T>::isUniform() const
{
    return m_elements.isUniform();
}

}// namespace cpp

#endif /*#ifndef SORTED_UNIQUE_VECTOR_HXX*/