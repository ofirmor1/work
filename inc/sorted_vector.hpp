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
    bool contains(int a_val) const;
    void remove(int a_val);
    int front() const;
    int back() const;
    void print(std::ostream&) const;

    size_t size() const;

private:
    std::vector<int> m_vec;
};

} // namespace name

#endif /*#ifndef SORTED_VECTOR_HPP*/