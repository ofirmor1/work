#ifndef STORE_HPP
#define STORE_HPP

#include <stddef.h>

namespace cpp
{

class Store
{
public:
    static const size_t CAPACITY = 16;
    Store(size_t a_size = CAPACITY);

    ~Store();
    Store(Store const& a_source);
    Store& operator=(Store const& a_source);

    int get(size_t a_index) const; //get value of element at index
    void set(size_t a_index, int a_value); //set value of element at index to v
    void reset(int a_value); //set value of all elements to v

    void print() const;

    size_t getCapacity() const;
    size_t getSize() const;

    int operator[](size_t a_index);

private:
    size_t m_size;
    size_t m_capacity;
    int* m_arr;
    
};

}//namespace cpp

#endif /*#ifndef STORE_HPP*/