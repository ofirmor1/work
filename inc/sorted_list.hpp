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
    bool contains(int a_val) const;
    void remove(int a_val);
    int front() const;
    int back() const;
    void print(std::ostream&) const;

    size_t size() const;

private:
    std::list<int> m_list;
};

} // namespace name

#endif /*#ifndef SORTED_LIST_HPP*/