#ifndef SORTED_VECTOR_BASE_HPP
#define SORTED_VECTOR_BASE_HPP

#include "sorted_container.hpp"
#include <vector>

namespace cpp
{

template <typename T>
class SortedVectorBase : public SortedContainer<T>
{

public:
    SortedVectorBase(size_t a_size = 0);
    ~SortedVectorBase() = 0;

    virtual void insert(T a_val) = 0;
    virtual size_t fill(T a_element, size_t a_times) = 0;

    size_t contains(T a_val) const;
    size_t remove(T a_val);

    T const& front() const;
    T const& back() const;
    
    size_t size() const;

    std::ostream& print(std::ostream& a_os = std::cout) const;

protected:
    typedef typename std::vector<T>::iterator Itr;
    typedef typename std::vector<T>::const_iterator ConstItr;
    typedef typename std::vector<T> Container;
    Container m_elements;
};

} // namespace name

#include "./inl/sorted_vector_base.hxx"

#endif /*#ifndef SORTED_VECTOR_BASE_HPP*/