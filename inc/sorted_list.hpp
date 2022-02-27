#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

#include "sorted_container.hpp"
#include "my_iterator.hpp"
#include <list>

namespace cpp
{

template <typename T>
class SortedList : public SortedContainer<T>
{

public:

    void insert(T a_element);
    size_t contains(T a_element) const;
    size_t remove(T a_element);

    T const& front() const;
    T const& back() const;

    MyIterator<T> begin();
    MyIterator<T> end();
    
    std::ostream& print(std::ostream& a_os) const;
    size_t size() const;

    T median() const;
    bool isSorted() const;
    bool isUniform() const;

private:
    typedef typename std::list<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator ConstItr;
    Container m_elements;
};

} // namespace cpp

#include "./inl/sorted_list.hxx"

#endif /*#ifndef SORTED_LIST_HPP*/