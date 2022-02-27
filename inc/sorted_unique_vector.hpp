#ifndef SORTED_UNIQUE_VECTOR_HPP
#define SORTED_UNIQUE_VECTOR_HPP

#include "sorted_vector.hpp"
#include "my_iterator.hpp"
#include <vector>

namespace cpp
{

template <typename T>
class SortedUniqueVector : public SortedVector<T>
{

public:
    // SortedUniqueVector();

    void insert(T a_val);
    size_t contains(T a_val) const;
    size_t remove(T a_val);

    T const& front() const;
    T const& back() const;

    MyIterator<T> begin();
    MyIterator<T> end();

    std::ostream& print(std::ostream& a_os = std::cout) const;

    size_t size() const;
    void fill(T a_elem, size_t a_times);

    T median() const;
    bool isSorted() const;
    bool isUniform() const;
    
private:
    typedef std::vector<T> Container;
    typedef typename Container::iterator Itr;
    typedef typename Container::const_iterator ConstItr;
    SortedVector<T> m_elements;
};

}// namespace cpp

#include "./inl/sorted_unique_vector.hxx"

#endif /*SORTED_UNIQUE_VECTOR_HPP*/