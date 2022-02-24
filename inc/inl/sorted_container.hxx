#ifndef SORTED_CONTAINER_HXX
#define SORTED_CONTAINER_HXX

#include <cassert>

namespace cpp
{

template <typename T>
inline SortedContainer<T>::SortedContainer()
{}

template <typename T>
inline SortedContainer<T>::~SortedContainer()
{}

template <typename T>
inline std::ostream& operator<<(std::ostream& a_os, SortedContainer<T> const& a_container)
{
    return a_container.print(a_os);
}

template <typename T>
inline void fill(SortedContainer<T>& a_container, int a_start, int a_end, int a_delta)
{
    assert((a_start < a_end && a_delta > 0) || (a_start > a_end && a_delta < 0));
    for (int i = a_start; i < a_end; i+=a_delta)
    {
        a_container.insert(i);
    }
}

template <typename T>
inline bool SortedContainer<T>::empty() const
{
    return size() == 0;
}

template <typename T>
inline bool empty(SortedContainer<T> const& a_container)
{
    return a_container.empty();
}

template <typename T>
inline void SortedContainer<T>::fill(T a_element, size_t a_times)
{
    while(a_times --> 0)
    {
        insert(a_element);
    }
}


}// namespace cpp 


#endif /*#ifndef SORTED_CONTAINER_HXX*/