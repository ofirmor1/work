#include <list>
#include "my_iterator.hpp"

namespace cpp
{

// template <typename T>
// SortedList<T>::SortedList()
// {}

template <typename T>
void SortedList<T>::insert(T a_element)
{
    if(m_elements.empty())
    {
        m_elements.push_back(a_element);
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
}

template <typename T>
size_t SortedList<T>::contains(T a_element) const
{
    ConstItr it = m_elements.begin();
    ConstItr end = m_elements.end();

    while (it != end && *it < a_element)
    {
        ++it;
    }

    size_t count = 0;
    while (it != end && *it == a_element)
    {
        ++it;
        ++count;
    }

    return count;   
}

template <typename T>
size_t SortedList<T>::remove(T a_element)
{
    Itr it = m_elements.begin();
    Itr end = m_elements.end();
    while (it != end && *it < a_element)
    {
        ++it;
    }

    size_t count = 0;
    while (it != end && *it == a_element)
    {
        it = m_elements.erase(it);
        ++count;
    }

    return count;   
}

template <typename T>
T SortedList<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T SortedList<T>::back() const
{
    return m_elements.back();
}

template <typename T>
MyIterator<T> SortedList<T>::begin() 
{
    return &m_elements.front();
}

template <typename T>
MyIterator<T> SortedList<T>::end() 
{
   MyIterator<T> last = &m_elements.back();
   ++last;
   return last;
}

template <typename T>
std::ostream& SortedList<T>::print(std::ostream& a_os) const
{
    return printContainer(m_elements, a_os);
}

template <typename T>
size_t SortedList<T>::size() const
{
    return m_elements.size();
}

template <typename T>
bool SortedList<T>::isSorted() const
{
    return isContainerSorted(m_elements);
}

template <typename T>
bool SortedList<T>::isUniform() const
{
    return isContainerUniformed(m_elements);
}


}// end of namespace cpp