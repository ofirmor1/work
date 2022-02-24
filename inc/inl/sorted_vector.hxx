#include <vector>
#include <numeric>
#include <algorithm>

#include "ball.hpp"

namespace cpp
{

template <typename T>
SortedVector<T>::SortedVector(size_t a_size)
{
    m_elements.reserve(a_size);
}

template <typename T>
void SortedVector<T>::insert(T a_element)
{
    if(m_elements.empty())
    {
        m_elements.push_back(a_element);
    }

    else
    {
        Itr it = m_elements.begin();
        Itr end = m_elements.end();

        while (it != end)
        {
            if(*it > a_element)
            {
                break;
            }
            it++;
        }
        m_elements.insert(it, a_element);
    }
}

template <typename T>
size_t SortedVector<T>::contains(T a_element) const
{
    ConstItr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    ConstItr end = m_elements.end();

    size_t count = 0;
    while(it != end && (*it) == a_element)
    {
        ++count;
        ++it;
    }

    return count;
}

template <typename T>
size_t SortedVector<T>::remove(T a_element)
{
    size_t count = 0;
    if(m_elements.empty())
    {
        return count;
    }
    
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    Itr end = m_elements.end();

    while(it != end && *it == a_element)
    {
        it = m_elements.erase(it);
        end = m_elements.end();
        ++count;
    }

    return count;
}

template <typename T>
T SortedVector<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T SortedVector<T>::back() const
{
    return m_elements.back();
}

template <typename T>
std::ostream& SortedVector<T>::print(std::ostream& a_os) const
{
    ConstItr it = m_elements.begin();
    ConstItr end = m_elements.end();

    a_os << "{";

    if(it != end)
    {
        a_os << *it++;
    }

    while(it != end)
    {
        a_os << ", " << *it++;
    }

    a_os << "}\n";
    
    return a_os;
}

template <typename T>
size_t SortedVector<T>::size() const
{
    return m_elements.size();
}

template <typename T>
void SortedVector<T>::fill(T a_element, size_t a_times)
{
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    m_elements.insert(it, a_times, a_element);
}
// SortedVector<T> const& a_container

inline bool cmp(Ball const& a, Ball const& b)
{
    return a < b;
}

template <typename T>
inline T& SortedVector<T>::median()
{
    Itr it = m_elements.begin();
    Itr end = m_elements.end();

    std::nth_element(it, it+2, end, cmp);
    std::cout << "\nThe median is " << m_elements[m_elements.size()/2] << '\n';
    // The consequence of the inequality of elements before/after the Nth one:
    // assert(std::accumulate(it, it+2, 0) < std::accumulate(it+2, end, 0));

    return m_elements[m_elements.size()/2];
}

} // end of namespace cpp