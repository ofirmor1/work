#ifndef SORTED_CONTAINER_HPP
#define SORTED_CONTAINER_HPP

#include <iostream>

namespace cpp
{

class SortedContainer
{

public:
    SortedContainer();
    virtual ~SortedContainer() = 0;

	virtual void insert(int a_val) = 0;
    virtual size_t contains(int a_val) const = 0;
    virtual size_t remove(int a_val) = 0;
    virtual int front() const = 0;
    virtual int back() const = 0;

    virtual size_t size() const = 0;
    bool empty() const;

    virtual std::ostream& print(std::ostream& = std::cout) const = 0;

    virtual void fill(int a_val, size_t times);
	
private:
	SortedContainer(const SortedContainer& a_container);
	SortedContainer& operator=(const SortedContainer& a_container); 

};

std::ostream& operator<<(std::ostream& a_os, SortedContainer const& a_container);
bool empty(SortedContainer const& a_container);
void fill(SortedContainer& a_container, int a_start, int a_end, int a_delta = 1);


} // namespace name

#include "./inl/sorted_container.hxx"

#endif /*#ifndef SORTED_CONTAINER_HPP*/