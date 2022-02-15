#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cassert>  
#include "utils.hpp"

namespace cpp
{
namespace detail_imp
{

template <typename T>
T const& selectPivot(T* a_arr, size_t a_from, size_t a_to)
{
    size_t mid = a_from + (a_to - a_from)/2;

    if (a_arr[mid] < a_arr[a_from])
    {
        swap(a_from, mid);
    } 
    if (a_arr[a_to] < a_arr[a_from]) 
    {
        swap(a_from, a_to);
    }
    if (a_arr[mid] < a_arr[a_to])
    {
        swap(mid, a_to);
    } 

    return a_arr[a_to];
}

template <typename T>
size_t partition(T* a_arr, size_t a_start , size_t a_end)
{
    assert(a_arr);
	// T pivot = selectPivot(a_arr, a_start, a_end); ???? get seg..
    size_t pivot = a_end;
    size_t j = a_start;
    for(size_t i = a_start; i < a_end; ++i)
    {
        if(a_arr[i] < a_arr[pivot])
        {
            using std::swap;
            swap(a_arr[i], a_arr[j]);
            ++j;
        }
    }

    swap(a_arr[j], a_arr[pivot]);
    return j;	
}

template <typename T>
void quickSortRec(T* a_arr, int a_start , int a_end)
{
    if(a_start < a_end)
    {
        size_t pivotIndex = partition (a_arr, a_start , a_end); 
        quickSortRec(a_arr , a_start , pivotIndex -1);
        quickSortRec(a_arr , pivotIndex + 1 , a_end);
    }		
}

} //end namespace detail_imp

template <typename T>
void quickSort(T* a_arr, size_t a_size)
{
	detail_imp::quickSortRec(a_arr, 0, a_size - 1);
}

template <typename T>
void printArray(T* a_arr, size_t a_size)
{
	for(size_t i = 0; i < a_size; ++i)
    {
        std::cout << a_arr[i] << " ";
    }
    
    std::cout << "\n\n";
}

} //end namespace cpp

