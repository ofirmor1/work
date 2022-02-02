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

    int get();
    void set(int a_val);
    ListItr next();
    bool equal(const ListItr &a_other) const;
    bool notEqual(const ListItr &a_other) const;
    bool search(Node* a_node, int a_key) const;

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
    int remove();
    Node* getHead();
    ListItr begin() const;
    ListItr end() const;
    size_t first() const;
    size_t last() const;
    LinkedList intersection(LinkedList& a, LinkedList& b);


    int size() const;
    bool isEmpty() const;
    void printList() const;
    void initListMemb();

private:
    Node* cutHead();
    int unbox(Node* const a_node);

private:
    Node* m_head;
    Node* m_tail;
    int m_size;
};

class BigInteger
{
public:
    BigInteger();

    ~BigInteger();
    BigInteger(const BigInteger& a_big);
    BigInteger& operator=(const BigInteger&);

    BigInteger(int a_num);
    BigInteger(long a_num);
    BigInteger(char a_num);

private:
    BigInteger add(BigInteger& a_num);
    BigInteger sub(BigInteger& a_num);
    BigInteger mul(BigInteger& a_num);

    void toList(int a_num);
    void toList(long a_num);
    void toList(char a_num);

    bool isPositive() const;
    int getSize() const;

    char* toString();
    bool isEmpty();


private:
    LinkedList m_digits;
    bool m_positive;
    int m_size;
};

#include "single_list.hxx"   

#endif /*ifndef SINGLE_LIST*/
