#ifndef SORTED_VECTOR_HPP
#define SORTED_VECTOR_HPP

#include "sorted_container.hpp"
#include <vector>

namespace cpp
{

template <typename T>
class SortedVector : public SortedContainer<T>
{

public:
    SortedVector(size_t a_size = 0);

    void insert(T a_val);
    size_t contains(T a_val) const;
    size_t remove(T a_val);
    T front() const;
    T back() const;
    std::ostream& print(std::ostream& a_os) const;

    size_t size() const;
    void fill(T a_elem, size_t a_times);

private:
    typedef std::vector<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator ConstItr;
    Container m_elements;
};

} // namespace name

#include "./inl/sorted_vector.hxx"

#endif /*#ifndef SORTED_VECTOR_HPP*/