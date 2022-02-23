#include "sorted_vector.hpp"
#include <vector>

namespace cpp
{

SortedVector::SortedVector(size_t a_size)
{
    m_vec.reserve(a_size);
}

void SortedVector::insert(int a_val)
{
    if(m_vec.empty())
    {
        m_vec.push_back(a_val);
    }

    else
    {
        std::vector<int>::iterator it = m_vec.begin();
        std::vector<int>::iterator end = m_vec.end();

        while (it != end)
        {
            if(*it > a_val)
            {
                break;
            }
            it++;
        }
        m_vec.insert(it, a_val);
    }        
}

bool SortedVector::contains(int a_val) const
{
    for (size_t i = 0; i < m_vec.size(); i++)
    {
        if(m_vec[i] == a_val)
        {
            return true;
        }
    }

    return false;   
}

void SortedVector::remove(int a_val)
{
    if(m_vec.empty())
    {
        return;
    }

    std::vector<int>::iterator it = m_vec.begin();
    std::vector<int>::iterator end = m_vec.begin();

    while (it != end)
    {
        if(*it == a_val)
        {
            m_vec.erase(it);
            break;
        }
        it++;
    }
}

int SortedVector::front() const
{
    return m_vec.front();
}

int SortedVector::back() const
{
    return m_vec.back();
}

void SortedVector::print(std::ostream& os) const
{
    std::vector<int>::const_iterator it = m_vec.begin();
    std::vector<int>::const_iterator end = m_vec.end();

    while (it != end)
    {
        os << *it++ << ", ";
    }
}

size_t SortedVector::size() const
{
    return m_vec.size();
}

} // end of namespace cpp