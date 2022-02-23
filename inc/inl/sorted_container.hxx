#ifndef SORTED_CONTAINER_HXX
#define SORTED_CONTAINER_HXX

#include <cassert>

namespace cpp
{

inline SortedContainer::SortedContainer()
{}

inline SortedContainer::~SortedContainer()
{}

inline std::ostream& operator<<(std::ostream& a_os, SortedContainer const& a_container)
{
    return a_container.print(a_os);
}

inline void fill(SortedContainer& a_container, int a_start, int a_end, int a_delta)
{
    assert((a_start < a_end && a_delta > 0) || (a_start > a_end && a_delta < 0));
    for (int i = a_start; i < a_end; i+=a_delta)
    {
        a_container.insert(i);
    }
}

inline bool SortedContainer::empty() const
{
    return size() == 0;
}

inline bool empty(SortedContainer const& a_container)
{
    return a_container.empty();
}

inline void SortedContainer::fill(int a_val, size_t a_times)
{
    while(a_times --> 0)
    {
        insert(a_val);
    }
}


}// namespace cpp 


#endif /*#ifndef SORTED_CONTAINER_HXX*/