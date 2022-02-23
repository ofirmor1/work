#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

#include "sorted_container.hpp"
#include <list>

namespace cpp
{

template <typename T>
class SortedList : public SortedContainer<T>
{

public:
    SortedList();

    void insert(T a_element);
    size_t contains(T a_element) const;
    size_t remove(T a_element);
    T front() const;
    T back() const;
    std::ostream& print(std::ostream& a_os) const;

    size_t size() const;

private:
    typedef typename std::list<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator ConstItr;
    Container m_elements;
};

} // namespace cpp

#include "./inl/sorted_list.hxx"

#endif /*#ifndef SORTED_LIST_HPP*/