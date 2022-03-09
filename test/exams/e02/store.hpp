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
    Store(Store const& a_arr);
    Store& operator=(Store const& a_arr);

    int get(size_t a_indx) const; //get value of element at index
    void set(size_t index, int a_value); //set value of element at index to v
    void reset(int a_value); //set value of all elements to v

    void print() const;

private:
    int* m_arr;
    size_t m_size;


};

}//namespace cpp

#endif /*#ifndef STORE_HPP*/