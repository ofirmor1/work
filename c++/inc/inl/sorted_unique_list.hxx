#ifndef SORTED_UNIQUE_LIST_HXX
#define SORTED_UNIQUE_LIST_HXX

#include <list>
#include "my_iterator.hpp"

namespace cpp
{

template <typename T>
void SortedUniqueList<T>::insert(T a_element)
{
    if(m_elements.empty())
    {
        m_elements.insert(a_element);
    }

    else
    {
        Itr it = m_elements.begin();
        Itr end = m_elements.end();

        while (it != end && *it < a_element)
        {   
            it++;
        }

        m_elements.insert(it, a_element);
    }   
    // return m_elements.insert(a_element);
    // Itr last = std::unique(m_elements.begin(), m_elements.end()); ???????????????
    // m_elements.erase(last, m_elements.end());
}

template <typename T>
size_t SortedUniqueList<T>::contains(T a_element) const
{
    return m_elements.contains(a_element);
}

template <typename T>
size_t SortedUniqueList<T>::remove(T a_element)
{
    return m_elements.remove(a_element);
}

template <typename T>
T const& SortedUniqueList<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T const& SortedUniqueList<T>::back() const
{
    return m_elements.back();
}

template <typename T>
MyIterator<T> SortedUniqueList<T>::begin()
{
    return m_elements.end();
}

template <typename T>
MyIterator<T> SortedUniqueList<T>::end()
{
    return m_elements.end();
}

template <typename T>
std::ostream& SortedUniqueList<T>::print(std::ostream& a_os) const
{
    return m_elements.print(a_os);
}

template <typename T>
size_t SortedUniqueList<T>::size() const
{
    return m_elements.size();
}

template <typename T>
T SortedUniqueList<T>::median() const
{
    return m_elements.median();
}

template <typename T>
bool SortedUniqueList<T>::isSorted() const
{
    return m_elements.isSorted();
}

template <typename T>
bool SortedUniqueList<T>::isUniform() const
{
    return m_elements.isUniform();
}

}// namespace cpp

#endif  /*#ifndef SORTED_UNIQUE_LIST_HXX*/