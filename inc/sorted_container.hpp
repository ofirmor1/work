#ifndef SORTED_CONTAINER_HPP
#define SORTED_CONTAINER_HPP

#include <iostream>

namespace cpp
{

class SortedContainer
{

public:
    SortedContainer(){}

	virtual void insert(int x) = 0;
    virtual bool contains(int x) const = 0;
    virtual void remove(int x) = 0;
    virtual int front() const = 0;
    virtual int back() const = 0;
    virtual void print(std::ostream&) const = 0;

    virtual size_t size() const = 0;
	
private:
	SortedContainer(const SortedContainer& a);
	SortedContainer& operator=(const SortedContainer& a); 

};

} // namespace name

#endif /*#ifndef SORTED_CONTAINER_HPP*/