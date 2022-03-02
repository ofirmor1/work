#ifndef SORTED_LIST_BASE_HXX
#define SORTED_LIST_BASE_HXX

#include <list>

namespace cpp
{

template <typename T>
void SortedListBase<T>::insert(T a_element)
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
size_t SortedListBase<T>::contains(T a_element) const
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
size_t SortedListBase<T>::remove(T a_element)
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
T const& SortedListBase<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T const& SortedListBase<T>::back() const
{
    return m_elements.back();
}

template <typename T>
std::ostream& SortedListBase<T>::print(std::ostream& a_os) const
{
    return printContainer(m_elements, a_os);
}

template <typename T>
size_t SortedListBase<T>::size() const
{
    return m_elements.size();
}

template <typename T>
size_t SortedListBase<T>::fill(T a_element, size_t a_times)
{
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    m_elements.insert(it, a_times, a_element);

    return a_times;
}


}// end of namespace cpp

#endif /*#ifndef SORTED_LIST_BASE_HXX*/