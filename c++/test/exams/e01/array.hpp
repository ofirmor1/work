#ifndef ARRAY_INT_H
#define ARRAY_INT_H

#include <stddef.h>
#include<iostream>

const int ARRAY_LENGTH = 10;
class ArrayOfInt
{
public:
    ArrayOfInt(size_t a_size);

    ~ArrayOfInt();
    ArrayOfInt(ArrayOfInt const& a_arr);
    ArrayOfInt& operator=(ArrayOfInt const& a_arr);

    void addItems();
    void removeItems();

    bool isFull() const;
    bool isEmpty() const;
    void print() const;

    void axioms();

    std::ostream& print(std::ostream& os) const;

private:
    bool m_isFull;
    size_t m_size; //num of items
    int* m_array[ARRAY_LENGTH];

};

std::ostream& operator<<(std::ostream& os, Rational const& a_array);

#endif /*ARRAY_INT_H*/
