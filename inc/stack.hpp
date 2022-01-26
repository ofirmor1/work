#ifndef STACK_H
#define STACK_H
class Stack
{
public:
//special member functions
//Constructor, ctor, initialize the stack 
    Stack(int _size = 100); 
    ~Stack();
    Stack(int* a_array, int a_arrSize);
    Stack(int* a_array, int a_arrSize, int a_formSize);
    Stack(const Stack &a_stack);

    void push(int x);
    int pop(); 
    int size() const;
    bool isEmpty() const;
    bool isFull() const; 
    void dump() const;  
    void empty(); 

    void pushArr(int* a_array, int arrSize);
    void popIntoArr(int* a_array, int a_arrSize);

private:
    void dumpElements() const;
    void axioms() const;

private:
    int m_tos;
    int m_capacity;
    int* m_elements;

    


};

Stack combineStacks(Stack a, Stack b);


#endif /*ifndef STACK_H*/