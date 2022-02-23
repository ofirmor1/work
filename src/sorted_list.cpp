#include "sorted_list.hpp"
#include <list>

namespace cpp
{

SortedList::SortedList()
{}

void SortedList::insert(int a_val)
{
    if(m_list.empty())
    {
        m_list.push_back(a_val);
    }

    else
    {
        std::list<int>::iterator it = m_list.begin();
        std::list<int>::iterator end = m_list.end();

        while (it != end && *it < a_val)
        {   
            it++;
        }

        m_list.insert(it, a_val);
    }        
}

bool SortedList::contains(int a_val) const
{
    std::list<int>::const_iterator it = m_list.begin();
    std::list<int>::const_iterator end = m_list.end();

    while (it != end)
    {
        if(*it == a_val)
        {
            return true;
        }
        it++;
    }

    return false;   
}

void SortedList::remove(int a_val)
{
    if(m_list.empty())
    {
        return;
    }
    
    std::list<int>::iterator it = m_list.begin();
    std::list<int>::iterator end = m_list.end();

    while (it != end)
    {
        if(*it == a_val)
        {
            m_list.erase(it);
            break;
        }
        it++;
    }
}

int SortedList::front() const
{
    return m_list.front();
}

int SortedList::back() const
{
    return m_list.back();
}

void SortedList::print(std::ostream& os) const
{
    std::list<int>::const_iterator it = m_list.begin();
    std::list<int>::const_iterator end = m_list.end();

    while(it != end)
    {
        os << *it << ", ";
        it++;
    }
}

size_t SortedList::size() const
{
    return m_list.size();
}

}// end of namespace cpp