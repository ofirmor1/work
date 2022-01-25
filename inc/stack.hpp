#ifndef STACK_H
#define STACK_H
class Stack
{
public:
//special member functions
//Constructor, ctor, initialize the stack 
    Stack(int _size = 100);    // member functions
//  @brief - destroy the stack 
//  @param - void
//  @return - void
//  @error - abort if stack is null
    ~Stack();
//  @brief - pushing x to the stack 
//  @param - int x
//  @return - void
//  @error - abort if stack is full
    void push(int x);

//  @brief - popping the itm in top of stack
//  @param - int x
//  @return - the item at top of stack 
//  @error - abort if stack is empty
    int pop(); 

//  @brief - return the sie of thee stack
//  @param - void
//  @return - size of stack
//  @error - none
    int size() const;

//  @brief - check if stack is empty
//  @param - void
//  @return - 0 if stack not empty, 1 if stack is empty
//  @error - none
    bool isEmpty() const;

//  @brief - check if stack is full
//  @param - void
//  @return - 0 if stack not full, 1 if stack is full
//  @error - none 
    bool isFull() const; 

//  @brief - printing all class members
//  @param - void
//  @return - void
//  @error - none 
    void dump() const;    // data member

//  @brief - will clear the stack
//  @param - void
//  @return - void
//  @error - none  
    void empty();  

private:
    void dumpElements() const;
    void axioms() const;

private:
    int *m_elements;
    int m_tos;
    int m_capacity;
};

#endif /*ifndef STACK_H*/