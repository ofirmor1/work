#ifndef SORTED_LIST_HPP
#define SORTED_LIST_HPP

#include "sorted_list_base.hpp"

namespace cpp
{

template <typename T>
class SortedList : public SortedListBase<T>
{
    SortedList(size_t a_size = 0);
    ~SortedList();
    void insert(T a_element);
    size_t fill(T a_element, size_t a_times);

};

} // namespace name

#include "./inl/sorted_list.hxx"

#endif /*#ifndef SORTED_LIST_HPP*/