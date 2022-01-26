#ifndef STACK_H
#define STACK_H
class Stack
{
public:
//special member functions
//Constructor, ctor, initialize the stack 
    Stack(size_t _size = 100); 
    ~Stack();
    Stack(int const* a_array, size_t a_stackSize);
    Stack(int const* a_array, size_t a_stackSize, size_t a_formSize);
    Stack(const Stack &a_stack);

    void empty();
    void push(int x);
    size_t pop(); 
    size_t top() const;

    void ensureCapacity(size_t n);    
    size_t capacity() const;
    size_t size() const;
    bool isEmpty() const;
    bool isFull() const; 

    void dump() const;  

    size_t pushArr(int const* a_array, size_t a_toPush);
    size_t popIntoArr(int* a_array, size_t a_toPop);

private:
    void dumpElements() const;
    void axioms() const;

private:
    size_t m_tos;
    size_t m_capacity;
    int* m_elements;
    
};

void combineStacks(Stack& a_destination, Stack& a_firstStack, Stack& a_secondStack);

#endif /*ifndef STACK_H*/