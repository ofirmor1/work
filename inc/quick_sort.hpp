#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "utils.hpp"
#include <cstddef>

namespace cpp
{

template <typename LessComparator, typename T>
// require T: swap, bool less(T const&, T const&)
void quickSort(T* a_arr, size_t a_size, LessComparator less = LessOp<T>());

} //namespace cpp

#include "./inl/quick_sort.hxx"
// ,  , 
#endif /*QUICK_SORT_HPP*/
