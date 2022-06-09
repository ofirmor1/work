#ifndef MY_ITERATOR_HPP
#define MY_ITERATOR_HPP

#include <iterator>

template <typename T>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
  
public:
    MyIterator(T const* x) :ptr(x) {}
    MyIterator(const MyIterator& mit) : ptr(mit.ptr) {}

    MyIterator& operator++() {++ptr;return *this;}
    MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
    bool operator==(const MyIterator& rhs) const {return ptr==rhs.ptr;}
    bool operator!=(const MyIterator& rhs) const {return ptr!=rhs.ptr;}
    T operator*() const {return *ptr;}
    const MyIterator operator+(const unsigned int val)  {const T* temp_ptr = ptr + val  ; return MyIterator(temp_ptr);}
    const MyIterator operator-(const unsigned int val)  {const T* temp_ptr = ptr - val  ; return MyIterator(temp_ptr);}

private:
    T const* ptr;
};

#endif /*#ifndef MY_ITERATOR_HPP*/