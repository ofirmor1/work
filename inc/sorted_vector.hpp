#ifndef SORTED_VECTOR_HPP
#define SORTED_VECTOR_HPP

#include "sorted_container.hpp"
#include <vector>

namespace cpp
{
    
class SortedVector : public SortedContainer
{

public:
    SortedVector(size_t a_size = 0);

    void insert(int a_val);
    size_t contains(int a_val) const;
    size_t remove(int a_val);
    int front() const;
    int back() const;
    std::ostream& print(std::ostream& a_os) const;

    size_t size() const;
    void fill(int a_val, size_t a_times);

private:
    typedef std::vector<int> Container;
    typedef Container::iterator Itr;
    typedef Container::const_iterator ConstItr;
    Container m_elements;
};

} // namespace name

#endif /*#ifndef SORTED_VECTOR_HPP*/