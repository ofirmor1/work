#ifndef SORTED_VECTOR_HPP
#define SORTED_VECTOR_HPP

#include "sorted_vector_base.hpp"

namespace cpp
{

template <typename T>
class SortedVector : public SortedVectorBase<T>
{
    SortedVector(size_t a_size = 0);
    ~SortedVector();
    void insert(T a_element);
    size_t fill(T a_element, size_t a_times);

};

} // namespace name

#include "./inl/sorted_vector.hxx"

#endif /*#ifndef SORTED_VECTOR_HPP*/