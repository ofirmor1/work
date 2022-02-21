#ifndef SINGLE_LIST
#define SINGLE_LIST

#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "single_list.hpp"
// #include "hash_set.hpp"

using namespace std;

template <typename T>
class Node
{
public:
    Node();
    Node(T a_data, Node* a_next);
    T getData();
    Node* getNext();
    void setData(T a_val);
    void setNext(Node* a_node);

private:
    T m_data;
    Node* m_next; 
};

template <typename T>
class ListItr: public std::iterator<std::input_iterator_tag, int>
{

public:
    ListItr();
    ListItr(Node<T>* a_node);

    T getData();
    void setData(T a_val);
    ListItr next();

    bool equal(const ListItr<T> &a_other) const;
    bool notEqual(const ListItr<T> &a_other) const;

    ListItr& operator=(Node<T>* a_node);

    ListItr& operator++();
    ListItr operator++(T);

    bool operator==(const ListItr& a_that);
    bool operator!=(const ListItr& a_that);
    
    int operator*() const;
    Node<T>* operator->() const;
// a->m
// *a = t
// ++a
// a++
// *a++

private:
    Node<T>* m_currNode;
};

//SingleLinkedList
template <typename T>
class LinkedList
{

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &a_list);
    LinkedList& operator=(LinkedList const& a_list);

    void addFirst(T const& a_val);
    void addLast(T const& a_val);

    T remove();
    ListItr<T> begin() const;
    ListItr<T> end() const;
    T first() const;
    T last() const;

    size_t size() const;
    bool isEmpty() const;
    void printList() const;
    bool contains(T a_val) const;
    
    LinkedList intersection(LinkedList<T> const& a) const;
    // LinkedList intersection(LinkedList const& a_first, LinkedList const& a_second);
    void initListMemb();

private:
    void axioms() const;
    Node<T>* cutHead();
    T unbox(Node<T>* const a_node);

private:
    Node<T>* m_sentinal;
    Node<T>* m_head;
    Node<T>* m_tail;
    int m_size;
};

template <typename T>
bool contains(LinkedList<T> const& a_list, T a_val);
template <typename T>
bool contains(ListItr<T> a_begin, ListItr<T> const a_end , T a_val);

// LinkedList& intersection(LinkedList const& a, LinkedList const& b, LinkedList& c);

#include "single_list.hxx"   

template <typename T>
Node<T>::Node(){}

template <typename T>
Node<T>::Node(T a_data, Node* a_next)
: m_data(a_data)
, m_next(a_next)
{
    assert(this != 0);
}

template <typename T>
ListItr<T>::ListItr()
:m_currNode(new Node<T>()){}

template <typename T>
ListItr<T>::ListItr(Node<T>* a_node)
:m_currNode(a_node){}

template <typename T>
LinkedList<T>::LinkedList()
: m_sentinal(new Node<T>())
, m_head(m_sentinal)
, m_tail(m_sentinal)
, m_size()
{
    m_sentinal->setNext(m_sentinal);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    for(int i = 1; i < m_size; i++)
    {
        remove();
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList const& a_source)
: m_sentinal(new Node<T>(0, m_sentinal))
, m_head(m_sentinal)
, m_tail(m_sentinal)
, m_size()
{    

    m_sentinal->setNext(m_sentinal);

    size_t i = a_source.size();;
    T * array = new int[m_size];
   
    ListItr<T> itr = a_source.begin();
    ListItr<T> last = a_source.end();

    while (itr.notEqual(last))
    {
        array[--i] = itr.getData();
        itr = itr.next();
    }
    for (i = 0; i < a_source.size(); i++)
    {
        addFirst(array[i]);
    }

    axioms();

    delete[] array;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> const&a_source)
{
    size_t i = a_source.size();;
    T * array = new T[m_size];
   
    ListItr<T> itr = a_source.begin();
    ListItr<T> last = a_source.end();

    while (itr.notEqual(last))
    {
        array[--i] = itr.getData();
        itr = itr.next();
    }

    for (i = 0; i < a_source.size(); i++)
    {
        addFirst(array[i]);
    }

    delete[] array;

    axioms();

    return *this;
}

template <typename T>
T LinkedList<T>::first() const
{
    assert(m_size >= 0);
    return m_head->getData();
}

template <typename T>
T LinkedList<T>::last() const
{
    assert(m_size >= 0);
    Node<T>* temp = m_head;
    for(int i = 1; i < m_size; i++)
    {
        temp = temp->getNext();
    }

    return temp->getData();

}

template <typename T>
inline Node<T>* LinkedList<T>::cutHead()
{
    assert(m_size);
    
    Node<T>* removeHead = m_head;
    m_head = m_head->getNext();
    m_size--;

    axioms();

    return removeHead;
}

template <typename T>
inline T LinkedList<T>::unbox(Node<T>* const a_node)
{
    assert(a_node);
    T data = a_node->getData();
    delete[] a_node;

    axioms();

    return data;
}

template <typename T>
T LinkedList<T>::remove()
{
   return unbox(cutHead());
}

template <typename T>
void LinkedList<T>::addFirst(T const& a_val)
{
    Node<T>* newNode = new Node<T>(a_val, m_head);
    m_head = newNode;
    if(isEmpty())
    {
        newNode->setNext(m_tail);
    }
    m_size++;

    axioms();
}

template <typename T>
void LinkedList<T>::addLast(T const& a_val)
{
    if(isEmpty())
    {
        this->m_head = new Node<T>();
        this->m_head->setData(a_val);
        this->m_head->setNext(m_tail);
    }
    else
    {
        Node<T>* curr = this->m_head;
        while(curr->getNext() != m_tail)
        {
            curr = curr->getNext();
        }
        Node<T>* newTail = new Node<T>();
        newTail->setData(a_val);
        newTail->setNext(m_sentinal);
        curr->setNext(newTail);
    }
    
    m_size++;

    axioms();
}

// staticsize_t myHashFunc(void* a_val)
// {
//     size_t data = *(size_t*)a_val;
//     return data * 2;
// }

// int myEqualityFunc(void* a_first, void* a_second)
// {
//     return (*(int*)a_first == *(int*)a_second) ? true:false;
// }

// size_t  intersection(LinkedList const& a_first, LinkedList const& a_second, LinkedList& a_list)
// {
//     Hash* hs = HashCreate(a_first.size(), myHashFunc, myEqualityFunc);
//     ListItr itr = a_first.begin();
//     ListItr end = a_first.end();
//     while(itr.notEqual(end))
//     {
//         int* item = new int;
//         *item = itr.getData();
//         HashInsert(hs, item);
//         itr.next();
//     }

//     ListItr itrB = a_first.begin();
//     ListItr endB = a_first.end();
//     while (itrB.notEqual(endB))
//     {
//         int toFind = itrB.getData();
//         int isFound = HashIsFound(hs, &toFind);
//         if(isFound)
//         {
//             a_list.addFirst(toFind);

//         }
//         itrB.next();
//     }

//     return a_list.size();
// }


// LinkedList LinkedList::intersection(LinkedList const& a_list) const
// {
//     LinkedList intersect;
//     Node* node = m_head;
//     while(node != m_sentinal)
//     {
//         if(a_list.contains(node->getData() == true))
//         {
//             intersect.addFirst(node->getData());
//         }
//         node = node->getNext();
//     }
//     return intersect;
// }

// LinkedList LinkedList::intersection(LinkedList const& a_first, LinkedList const& a_second)
// {

// }
// size_t intersect (LinkedList const& a_first, LinkedList const& a_second, LinkedList& a_result);
// LinkedList& intersect (LinkedList const& a_first, LinkedList const& a_second, LinkedList& a_result);
// ListItr itr = this->begin();
//     ListItr itrEnd = end();
//     while(itr.notEqual(this->end()))
//     {
//         if(itr.getData() == a_val)
//         {
//             return true;
//         }
//         itr.next();
//     }
//     return false;

// another opt - return ::contains(*this, a_val);
// static bool contains_jump(LinkedList const& a_list, int a_val)
// {
//     return contains(a_list, a_val);
// }

template <typename T>
bool LinkedList<T>::contains(T a_val) const
{ 
    return ::contains(*this, a_val);

}

template <typename T>
bool contains(LinkedList<T> const& a_list, T a_val)
{ 
    return contains(a_list.begin(), a_list.end(), a_val);
}

template <typename T>
bool contains(ListItr<T> a_begin, ListItr<T> a_end , T a_val)
{ 
    a_end.setData(a_val);
    while(a_begin.getData() != a_val)
    {
        a_begin.next();
    }

    return a_begin.notEqual(a_end);
}

template <typename T>
void LinkedList<T>::axioms() const
{
   assert(m_size >= 0);
   assert(m_head != 0);
   assert(m_tail != 0);
   assert(m_sentinal != 0);
   assert(m_sentinal -> getNext() == m_sentinal);

}

#include "single_list.hxx"
#endif /*SINGLE_LIST*/
