#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <cstddef>

namespace cpp
{

template <typename T>
//require: <
struct LessOp
{
    bool operator()(const T& a, const T& b)
    {
        return a < b;
    }
};

template <typename T>
// require T: swap, bool less(T const&, T const&)
void quickSort(T* a_arr, size_t a_size);

} //namespace cpp

#include "./inl/quick_sort.hxx"
// , typename Less , Less less
#endif /*QUICK_SORT_HPP*/
