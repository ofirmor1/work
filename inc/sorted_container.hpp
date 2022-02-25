#ifndef SORTED_CONTAINER_HPP
#define SORTED_CONTAINER_HPP

#include <iostream>
#include "my_iterator.hpp"

namespace cpp
{

template <typename T>
class SortedContainer
{

public:
    typedef T value_type;
    SortedContainer();
    virtual ~SortedContainer() = 0;

    virtual size_t contains(T a_element) const = 0;
    virtual size_t remove(T a_element) = 0;
    virtual void insert(T a_element) = 0;

    virtual T front() const = 0;
    virtual T back() const = 0;

    virtual MyIterator<T> begin() = 0;
    virtual MyIterator<T> end() = 0;

    // size_t operator[](size_t a_indx){return a_indx; }

    virtual size_t size() const = 0;
    bool empty() const;

    virtual std::ostream& print(std::ostream& = std::cout) const = 0;

    virtual void fill(T a_val, size_t times);

private:
	SortedContainer<T>(const SortedContainer<T>& a_container);
	SortedContainer<T>& operator=(const SortedContainer<T>& a_container); 

};

template <typename T>
typename T::value_type containerMedian(T const& a_container);

template <typename T>
bool isContainerSorted(T const& a_container);

template <typename T>
bool isContainerUniformed(T const& a_container);

template <typename T>
std::ostream& printContainer(T const& a_container, std::ostream& a_os = std::cout);

template <typename T>
std::ostream& operator<<(std::ostream& a_os, SortedContainer<T> const& a_container);

template <typename T>
bool empty(SortedContainer<T> const& a_container);

template <typename T>
void fill(SortedContainer<T>& a_container, int a_start, int a_end, int a_delta = 1);


} // namespace name

#include "./inl/sorted_container.hxx"

#endif /*#ifndef SORTED_CONTAINER_HPP*/