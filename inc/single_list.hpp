#ifndef SINGLE_LIST
#define SINGLE_LIST

static int const CAPACITY = 100;

struct Node
{
    int m_data;
    Node* m_next; 
};

//SingleLinkedList
class LinkedList
{
public:
    LinkedList();
    /*~LinkedList();*/
    LinkedList(const LinkedList &a_list);
    LinkedList& operator=(LinkedList const& a_list);

    void add(int a_val);
    void remove();
    size_t first() const;
    size_t last() const;


    int size() const;
    bool isEmpty() const;
    void printList() const;
    void initListMemb();

private:
    Node* m_head;
    Node* m_tail;
    int m_size;
};

class Itr
{
public:

private:
};

#include "../inc/inl/single_list.hxx"
#include "single_list.hxx"   

#endif /*ifndef SINGLE_LIST*/
