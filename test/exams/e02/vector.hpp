#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <vector>

namespace cpp
{

class Vector
{

public:    
    Vector(size_t a_size = 16);

    int sumElements(size_t a_from, size_t a_to) const;
    void Update(size_t a_index, int a_value);

    void insert(int a_value);
    size_t getSize() const;

    int operator[](size_t a_index);

private:
    // typedef typename std::vector<int>::iterator Itr;
    // typedef typename std::vector<T>::const_iterator ConstItr;
    // typedef typename std::list<T> Container;
    std::vector<int> m_vec;

};

}//namespace cpp

#endif /*#ifndef VECTOR_HPP*/