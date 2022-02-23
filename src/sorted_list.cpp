#include "sorted_list.hpp"
#include <list>

namespace cpp
{

SortedList::SortedList()
{}

void SortedList::insert(int a_val)
{
    if(m_elements.empty())
    {
        m_elements.push_back(a_val);
    }

    else
    {
        Itr it = m_elements.begin();
        Itr end = m_elements.end();

        while (it != end && *it < a_val)
        {   
            it++;
        }

        m_elements.insert(it, a_val);
    }        
}

size_t SortedList::contains(int a_val) const
{
    ConstItr it = m_elements.begin();
    ConstItr end = m_elements.end();

    while (it != end && *it < a_val)
    {
        ++it;
    }

    size_t count = 0;
    while (it != end && *it == a_val)
    {
        ++it;
        ++count;
    }

    return count;   
}

size_t SortedList::remove(int a_val)
{
    Itr it = m_elements.begin();
    Itr end = m_elements.end();
    while (it != end && *it < a_val)
    {
        ++it;
    }

    size_t count = 0;
    while (it != end && *it == a_val)
    {
        it = m_elements.erase(it);
        ++count;
    }

    return count;   
}

int SortedList::front() const
{
    return m_elements.front();
}

int SortedList::back() const
{
    return m_elements.back();
}

std::ostream& SortedList::print(std::ostream& a_os) const
{
    ConstItr it = m_elements.begin();
    ConstItr end = m_elements.end();

    while(it != end)
    {
        a_os << *it << ", ";
        it++;
    }
    
    return a_os;
}

size_t SortedList::size() const
{
    return m_elements.size();
}



}// end of namespace cpp