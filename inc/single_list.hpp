#ifndef SINGLE_LIST
#define SINGLE_LIST

class Node
{
public:
    Node();
    Node(int a_data, Node* a_next);
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
    bool operator!=(ListItr that) const;

    int getData();
    void setData(int a_val);
    ListItr next();
    bool equal(const ListItr &a_other) const;
    bool notEqual(const ListItr &a_other) const;

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

    void addFirst(int const a_val);
    void addLast(int const a_val);


    // void add(int a_val);
    int remove();
    ListItr begin() const;
    ListItr end() const;
    size_t first() const;
    size_t last() const;

    int size() const;
    bool isEmpty() const;
    void printList() const;
    bool contains(int a_val) const;
    LinkedList intersection(LinkedList const& a) const;
    // LinkedList intersection(LinkedList const& a_first, LinkedList const& a_second);
    void initListMemb();

private:
    void axioms() const;
    Node* cutHead();
    int unbox(Node* const a_node);

private:
    Node* m_sentinal;
    Node* m_head;
    Node* m_tail;
    int m_size;
};

// LinkedList& intersection(LinkedList const& a, LinkedList const& b, LinkedList& c);

#include "single_list.hxx"   

#endif /*ifndef SINGLE_LIST*/
