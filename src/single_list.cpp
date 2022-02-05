#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "single_list.hpp"

using namespace std;

Node::Node(){}

Node::Node(int a_data, Node* a_next)
: m_data(a_data)
, m_next(a_next)
{
    assert(this != 0);
}

ListItr::ListItr()
:m_currNode(new Node()){}

ListItr::ListItr(Node* a_node)
:m_currNode(a_node){}

LinkedList::LinkedList()
: m_sentinal(new Node(0, m_sentinal))
, m_head(m_sentinal)
, m_tail(m_sentinal)
, m_size()
{
    m_sentinal->setNext(m_sentinal);
}

LinkedList::~LinkedList()
{
    for(int i = 1; i < m_size; i++)
    {
        remove();
    }
}

LinkedList::LinkedList(LinkedList const& a_source)
: m_sentinal(new Node(0, m_sentinal))
, m_head(m_sentinal)
, m_tail(m_sentinal)
, m_size()
{    

    m_sentinal->setNext(m_sentinal);

    int i = a_source.size();;
    int * array = new int[m_size];
   
    ListItr itr = a_source.begin();
    ListItr last = a_source.end();

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

    delete [] array;
}

LinkedList& LinkedList::operator=(LinkedList const&a_source)
{
    int i = a_source.size();;
    int * array = new int[m_size];
   
    ListItr itr = a_source.begin();
    ListItr last = a_source.end();

    while (itr.notEqual(last))
    {
        array[--i] = itr.getData();
        itr = itr.next();
    }
    for (i = 0; i < a_source.size(); i++)
    {
        addFirst(array[i]);
    }
    delete [] array;

    axioms();

    return *this;
}

bool ListItr::operator!=(ListItr that) const
{
    return (this->m_currNode != that.m_currNode);
}

size_t LinkedList::first() const
{
    assert(m_size >= 0);
    return m_head->getData();
}

size_t LinkedList::last() const
{
    assert(m_size >= 0);
    Node* temp = m_head;
    for(int i = 1; i < m_size; i++)
    {
        temp = temp->getNext();
    }

    return temp->getData();

}

inline Node* LinkedList::cutHead()
{
    assert(m_size);
    
    Node* removeHead = m_head;
    m_head = m_head->getNext();
    m_size--;

    axioms();

    return removeHead;
}

inline int LinkedList::unbox(Node* const a_node)
{
    assert(a_node);
    int data = a_node->getData();
    delete a_node;

    axioms();

    return data;
}

//int LinkedList::remove(int& a_val)
int LinkedList::remove()
{
   return unbox(cutHead());
}

void LinkedList::addFirst(int const a_val)
{
    Node* newNode = new Node(a_val, m_head);
    m_head = newNode;
    if(isEmpty())
    {
        newNode->setNext(m_tail);
    }
    m_size++;

    axioms();
}

void LinkedList::addLast(int const a_val)
{
    if(isEmpty())
    {
        this->m_head = new Node();
        this->m_head->setData(a_val);
        this->m_head->setNext(m_tail);
    }
    else
    {
        Node* curr = this->m_head;
        while(curr->getNext() != m_tail)
        {
            curr = curr->getNext();
        }
        Node* newTail = new Node();
        newTail->setData(a_val);
        newTail->setNext(m_sentinal);
        curr->setNext(newTail);
    }
    
    m_size++;

    axioms();
}

LinkedList LinkedList::intersection(LinkedList const& a_list) const
{
    LinkedList intersect;
    Node* node = m_head;
    while(node != m_sentinal)
    {
        if(a_list.contains(node->getData() == true))
        {
            intersect.addFirst(node->getData());
        }
        node = node->getNext();
    }
    return intersect;
}

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
bool LinkedList::contains(int a_val) const
{ 
    ListItr itr = this->begin();   
    m_tail->setData(a_val);
    while(itr.getData() != a_val)
    {
        itr.next();
    }

    return itr.notEqual(this->end()) ? true : false;
}

bool contains(LinkedList const& a_list, int a_val)
{ 
    return a_list.contains(a_val);
}

bool contains(ListItr const& a_begin, ListItr const& a_end , int a_val)
{ 
    ListItr itr = a_begin;
    while(itr.notEqual(a_end))
    {
        if(itr.getData() == a_val)
        {
            return true;
        }
        itr.next();
    }
    return false;
}

void LinkedList::axioms() const
{
   assert(m_size >= 0);
   assert(m_head != 0);
   assert(m_tail != 0);
   assert(m_sentinal != 0);
   assert(m_sentinal -> getNext() == m_sentinal);

}