#ifndef SINGLE_LIST
#define SINGLE_LIST

class Node
{
public:
    int getData();
    Node* getNext();
    void setData(int a_val);
    void setNext(Node* a_node);

private:
    int m_data;
    Node* m_next; 
};

class ListItr
{
public:
    ListItr();
    ListItr(Node* a_node);

    int get();
    ListItr next();
    bool equals(const ListItr &a_first) const;


private:
    Node* m_currNode;
};

//SingleLinkedList
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &a_list);
    LinkedList& operator=(LinkedList const& a_list);

    void add(int a_val);
    void remove();
    ListItr begin() const;
    ListItr end() const;
    size_t first() const;
    size_t last() const;


    int size() const;
    bool isEmpty() const;
    void printList() const;
    void initListMemb();

    static void copyList();

private:
    Node* m_head;
    Node* m_tail;
    int m_size;
};
// #include "../inc/inl/single_list.hxx"
#include "single_list.hxx"   

#endif /*ifndef SINGLE_LIST*/
