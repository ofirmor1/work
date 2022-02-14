#include <iostream>
#include <cstring>
#include <stddef.h>

namespace cpp
{

template <typename T>
class Array
{
private:
    size_t m_size;
    T* m_arr;

private:
    void axioms() const;

public:
    Array(size_t a_size = 16);

    ~Array();
    Array(Array const& a_arr);
    Array& operator=(Array const& a_arr);

    void at(size_t a_indx, T a_val);
    T at(size_t a_indx) const;

    T& operator[](size_t a_indx);
    T const& operator[](size_t a_indx) const;

    size_t size() const;
};

template <typename T>
Array<T>::Array(size_t a_size)
: m_size(a_size)
, m_arr(new T[m_size])
{
    axioms();
}

template <typename T>
Array<T>::~Array()
{
    delete[] m_arr;
}

template <typename T>
Array<T>::Array(Array const& a_arr)
: m_size(a_arr.m_size)
, m_arr(new T[m_size])
{
    memcpy(m_arr, a_arr.m_arr, m_size * sizeof(int));
    axioms();
}

template <typename T>
Array<T>& Array<T>::operator=(Array const& a_arr)
{
    T* copy = new int[a_arr.m_size];
    memcpy(copy, a_arr.m_arr, a_arr.m_size * sizeof(int));

    m_size = a_arr.m_size;
    swap(m_arr, copy);
    delete[] copy;

    axioms();
    return *this;
}

template <typename T>
void Array<T>::at(size_t a_indx, T a_val)
{
    assert(a_indx < m_size);
    m_arr[a_indx] = a_val;
    axioms();
}

template <typename T>
T Array<T>::at(size_t a_indx) const
{
    assert(a_indx < m_size);
    return m_arr[a_indx];
}

template <typename T>
size_t Array<T>::size() const
{
   return m_size;
}

template <typename T>
T& Array<T>::operator[](size_t a_indx)
{
    return m_arr[a_indx];
}

template <typename T>
T const& Array<T>::operator[](size_t a_indx) const
{
    return m_arr[a_indx];
}


} // namespace cpp





