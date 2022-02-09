#ifndef ARRAY_INT_H
#define ARRAY_INT_H

#include <stddef.h>

const int ARRAY_LENGTH = 10;
class ArrayOfInt
{
public:
    ArrayOfInt();
    ArrayOfInt(int* a_array, size_t a_size);

    ~ArrayOfInt();
    ArrayOfInt(ArrayOfInt const& a_arr);
    ArrayOfInt& operator=(ArrayOfInt const& a_arr);

    void addItems();
    void removeItems();

    bool isFull() const;
    bool isEmpty() const;
    void print() const;

private:
    int* m_array[ARRAY_LENGTH];
    bool m_isFull;
    size_t m_size; //num of items
};

#endif /*ARRAY_INT_H*/
