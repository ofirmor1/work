#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

#include "sorted_container.hpp"
#include <list>

namespace cpp
{

class SortedList : public SortedContainer
{

public:
    SortedList();

    void insert(int a_val);
    size_t contains(int a_val) const;
    size_t remove(int a_val);
    int front() const;
    int back() const;
    std::ostream& print(std::ostream& a_os) const;

    size_t size() const;

private:
    typedef std::list<int> Container;
    typedef Container::iterator Itr;
    typedef Container::const_iterator ConstItr;
    Container m_elements;
};

} // namespace cpp

#endif /*#ifndef SORTED_LIST_HPP*/