#ifndef SORTED_CONTAINER_HXX
#define SORTED_CONTAINER_HXX

#include <cassert>

namespace cpp
{

template <typename T>
SortedContainer<T>::SortedContainer()
{}

template <typename T>
SortedContainer<T>::~SortedContainer()
{}

template <typename T>
std::ostream& operator<<(std::ostream& a_os, SortedContainer<T> const& a_container)
{
    return a_container.print(a_os);
}

template <typename T>
std::ostream& printContainer(T const& a_container, std::ostream& a_os)
{
    typename T::const_iterator it = a_container.begin(); 
    typename T::const_iterator end = a_container.end();  
    
    a_os << '{';

    if(it != end)
    {
        a_os << *it++;  
    }

    while(it != end)
    {
        a_os << ", " << *it++; 
    }
    a_os << "}\n"; 

    return a_os;
}

template <typename T>
void fill(SortedContainer<T>& a_container, int a_start, int a_end, int a_delta)
{
    assert((a_start < a_end && a_delta > 0) || (a_start > a_end && a_delta < 0));
    for (int i = a_start; i < a_end; i+=a_delta)
    {
        a_container.insert(i);
    }
}

template <typename T>
bool SortedContainer<T>::empty() const
{
    return size() == 0;
}

template <typename T>
bool empty(SortedContainer<T> const& a_container)
{
    return a_container.empty();
}

template <typename T>
size_t SortedContainer<T>::fill(T a_element, size_t a_times)
{
    while(a_times --> 0)
    {
        insert(a_element);
    }

    return a_times;
}

// template <typename T>
// typename T::value_type const& containerMedian(T const& a_container)
// {
//     assert(a_container.size() > 0);
//     MyIterator<T> it = a_container.begin(); 
//     while (it < a_container.size()/2)
//     {
//         it++;
//     }    

//     return (a_container.size()%2 == 0) ? *it : *(++it);
// }

template <typename T>
bool isContainerSorted(T const& a_container)
{
    typename T::const_iterator it = a_container.begin();
    typename T::const_iterator end = a_container.end();

    while(it != end)
    {
        if( *it > *it++)
        {
            return false;
        }
    }

    return true;
}

template <typename T>
bool isContainerUniformed(T const& a_container)
{
    typename T::const_iterator it = a_container.begin();
    typename T::const_iterator end = a_container.end();

    while(it != end)
    {
        if( !( *it++ == a_container.front()) ) 
        {
            return false;
        }
    }

    return true;
}

}// namespace cpp 

#endif /*#ifndef SORTED_CONTAINER_HXX*/