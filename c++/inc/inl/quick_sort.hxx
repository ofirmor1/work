#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cassert>  
#include "utils.hpp"

const size_t THRESHOLD = 19; // TODO: check why bubble sort (above 19) not working on char array.

namespace cpp
{

namespace detail_imp
{

template <typename LessComparator, typename T>
size_t scanRight(const T* a_arr, size_t a_first, const size_t a_last, T const& a_pivot, LessComparator less)
{
    while(!(a_pivot < a_arr[a_first]) && a_first <= a_last)
    {
        ++a_first;
    }
    
    return a_first;
}

template <typename LessComparator, typename T>
size_t scanLeft(const T* a_arr, size_t a_last, T const& a_pivot, LessComparator less)
{
    while(a_pivot < a_arr[a_last])
    {
        --a_last;
    }

    return a_last;
}
template <typename T>
T& selectPivot(T* a_arr, size_t a_first, size_t a_last)
{
    // size_t mid = a_first + (a_last - a_first)/2;

    // if (a_arr[mid] < a_arr[a_first])
    // {
    //     swap(a_first, mid);
    // } 
    // if (a_arr[a_last] < a_arr[a_first]) 
    // {
    //     swap(a_first, a_last);
    // }
    // if (a_arr[mid] < a_arr[a_last])
    // {
    //     swap(mid, a_last);
    // } 

    // return a_arr[a_last];
    return a_arr[a_first];
}

template <typename LessComparator, typename T>
size_t partition(T* a_arr, size_t a_first , size_t a_last, T& a_pivot, LessComparator less)
{
    
    for(size_t i = a_first; i < a_last; ++i)
    {
        a_last = scanLeft(a_arr, a_last, a_pivot, less);
        a_first = scanRight(a_arr, a_first, a_last, a_pivot, less);
        
        if(a_first < a_last)
        {
            using std::swap;
            swap(a_arr[a_first], a_arr[a_last]);
        }
    }
    using std::swap;
    swap(a_pivot, a_arr[a_last]);
    return a_last;	
}

template <typename LessComparator, typename T>
void insertion(T* a_arr, size_t a_start , size_t a_last, LessComparator less)
{
    size_t i, j;
    (void)j;
    i = a_start;
    while(i < a_start)
    {
        for (size_t j = i+1; j > 0; --j)
        {
            if(less(a_arr[j], a_arr[j-1]))
            {
                using std::swap;
                swap(a_arr[j], a_arr[j-1]);
            } 
            else
            {
                break;  
            }  
        }
        ++i;
    }
}

template <typename LessComparator, typename T>
void quickSortRec(T* a_arr, size_t a_start , size_t a_last, LessComparator less)
{
    if(a_start < a_last)
    {
        if(a_last - a_start == THRESHOLD)
        {
             insertion(a_arr, a_start, a_last, less);
        }

        T& pivot = selectPivot(a_arr, a_start, a_last);
        size_t posOfPivot = partition (a_arr, a_start , a_last, pivot, less); 
 
            if(posOfPivot > 0)
            {

                quickSortRec(a_arr , a_start , posOfPivot - 1, less);
            }

            if(posOfPivot < a_last)
            {
                quickSortRec(a_arr , posOfPivot + 1 , a_last, less);
            }
    }		
}

} //end namespace detail_imp

template <typename T>
void printArray(T* a_arr, size_t a_size)
{
	for(size_t i = 0; i < a_size; ++i)
    {
        std::cout << a_arr[i] << " ";
    }
    
    std::cout << "\n\n";
}

}

namespace cpp
{

template <typename LessComparator, typename T>
void quickSort(T* a_arr, size_t a_size, LessComparator less)
{
    if(!a_arr || a_size <= 1)
    {
        return;
    }
    
	detail_imp::quickSortRec(a_arr, 0, a_size - 1, less);
} 

} // namespace cpp

