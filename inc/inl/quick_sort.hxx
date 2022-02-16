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

template <typename T>
size_t scanRight(const T* a_arr, size_t a_first, const size_t a_last, T const& a_pivot)
{
    while(!(a_pivot < a_arr[a_first]) && a_first <= a_last)
    {
        ++a_first;
    }
    
    return a_first;
}

template <typename T>
size_t scanLeft(const T* a_arr, size_t a_last, T const& a_pivot)
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

template <typename T>
size_t partition(T* a_arr, size_t a_first , size_t a_last, T& a_pivot)
{
    
    for(size_t i = a_first; i < a_last; ++i)
    {
        a_last = scanLeft(a_arr, a_last, a_pivot);
        a_first = scanRight(a_arr, a_first, a_last, a_pivot);
        
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

template <typename T>
void bubbleSort(T* a_arr, size_t a_start , size_t a_last)
{
    for (size_t i = a_start; i < a_last; i++)
    {
        if(a_arr[i+1] < a_arr[i])
        {
            printf("1 ");
            using std::swap;
            swap(a_arr[i], a_arr[i+1]);
        }   
    }
}

template <typename T>
void quickSortRec(T* a_arr, size_t a_start , size_t a_last)
{
    if(a_start < a_last)
    {
         
        T& pivot = selectPivot(a_arr, a_start, a_last);
        size_t posOfPivot = partition (a_arr, a_start , a_last, pivot); 
        
        {
            if(posOfPivot > 0)
            {
                if(posOfPivot > THRESHOLD)
                {
                    quickSortRec(a_arr , a_start , posOfPivot - 1);
                }
                bubbleSort(a_arr, a_start, posOfPivot);
                
            }
            if(posOfPivot < a_last)
            {
                if(posOfPivot < a_last - THRESHOLD)
                {
                    quickSortRec(a_arr , posOfPivot + 1 , a_last);
                }
                bubbleSort(a_arr, posOfPivot, a_last);
            }
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

template <typename T>
void quickSort(T* a_arr, size_t a_size)
{
    if(!a_arr || a_size <= 1)
    {
        return;
    }
    
	detail_imp::quickSortRec(a_arr, 0, a_size - 1);
} 

} // namespace cpp

