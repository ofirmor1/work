#ifndef SORTED_LIST_BASE_HPP
#define SORTED_LIST_BASE_HPP

#include "sorted_container.hpp"
#include <list>

namespace cpp
{

template <typename T>
class SortedListBase : public SortedContainer<T>
{

public:
    SortedListBase(size_t a_size = 0);
    ~SortedListBase() = 0;

    virtual void insert(T a_element) = 0;
    virtual size_t fill(T a_element, size_t a_times) = 0;

    size_t contains(T a_element) const;
    size_t remove(T a_element);

    T const& front() const;
    T const& back() const;
    
    size_t size() const;

    std::ostream& print(std::ostream& a_os = std::cout) const;

protected:
    typedef typename std::list<T>:: Itr;
    typedef typename std::list<T>::const_iterator ConstItr;
    typedef typename std::list<T> Container;
    Container m_elements;
};

} // namespace name

#include "./inl/sorted_list_base.hxx"

#endif /*#ifndef SORTED_LIST_BASE_HPP*/