#ifndef MIN_STACK
#define MIN_STACK

#include <stddef.h>
#include "stack.hpp"

const size_t CAPACITY = 64;

class MinStack
{
public:
    MinStack(size_t a_cap = CAPACITY);

    void push(int a_data);
    int pop();
   
    int top() const;
    int minVal() const;
    bool isFull() const;
    bool isEmpty() const;

private:  
    Stack m_data;
    Stack m_min;
};

#endif /*MIN_STACK*/

