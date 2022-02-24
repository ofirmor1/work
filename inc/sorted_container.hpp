#ifndef SORTED_CONTAINER_HPP
#define SORTED_CONTAINER_HPP

#include <iostream>

namespace cpp
{

template <typename T>
class SortedContainer
{

public:
    SortedContainer();
    virtual ~SortedContainer() = 0;

	virtual void insert(T a_element) = 0;
    virtual size_t contains(T a_element) const = 0;
    virtual size_t remove(T a_element) = 0;
    virtual T front() const = 0;
    virtual T back() const = 0;

    virtual size_t size() const = 0;
    bool empty() const;

    virtual std::ostream& print(std::ostream& = std::cout) const = 0;

    virtual void fill(T a_val, size_t times);

    // virtual T& median(SortedVector<T> const& a_container);
	
private:
	SortedContainer<T>(const SortedContainer<T>& a_container);
	SortedContainer<T>& operator=(const SortedContainer<T>& a_container); 

};

template <typename T>
std::ostream& operator<<(std::ostream& a_os, SortedContainer<T> const& a_container);

template <typename T>
bool empty(SortedContainer<T> const& a_container);

template <typename T>
void fill(SortedContainer<T>& a_container, int a_start, int a_end, int a_delta = 1);


} // namespace name

#include "./inl/sorted_container.hxx"

#endif /*#ifndef SORTED_CONTAINER_HPP*/