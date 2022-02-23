#include "sorted_vector.hpp"
#include <vector>

namespace cpp
{

SortedVector::SortedVector(size_t a_size)
{
    m_elements.reserve(a_size);
}

void SortedVector::insert(int a_val)
{
    if(m_elements.empty())
    {
        m_elements.push_back(a_val);
    }

    else
    {
        Itr it = m_elements.begin();
        Itr end = m_elements.end();

        while (it != end)
        {
            if(*it > a_val)
            {
                break;
            }
            it++;
        }
        m_elements.insert(it, a_val);
    }
}

size_t SortedVector::contains(int a_val) const
{
    ConstItr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_val);
    ConstItr end = m_elements.end();

    size_t count = 0;
    while(it != end && (*it) == a_val)
    {
        ++count;
        ++it;
    }

    return count;
}

size_t SortedVector::remove(int a_val)
{
    size_t count = 0;
    if(m_elements.empty())
    {
        return count;
    }
    
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_val);
    Itr end = m_elements.end();

    while(it != end && *it == a_val)
    {
        it = m_elements.erase(it);
        end = m_elements.end();
        ++count;
    }

    return count;
}

int SortedVector::front() const
{
    return m_elements.front();
}

int SortedVector::back() const
{
    return m_elements.back();
}

std::ostream& SortedVector::print(std::ostream& a_os) const
{
    ConstItr it = m_elements.begin();
    ConstItr end = m_elements.end();

    while (it != end)
    {
        a_os << *it++ << ", ";
    }

    return a_os;
}

size_t SortedVector::size() const
{
    return m_elements.size();
}

void SortedVector::fill(int a_val, size_t a_times)
{
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_val);
    m_elements.insert(it, a_times, a_val);
}

} // end of namespace cpp