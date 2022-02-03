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
{}

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

LinkedList::LinkedList(const LinkedList &a_source)
: m_sentinal(new Node(0, m_sentinal))
, m_head(m_sentinal)
, m_tail(m_sentinal)
, m_size()
{
    initListMemb();
    
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
}

LinkedList& LinkedList::operator=(LinkedList const&a_source)
{
    initListMemb();
    
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
    return *this;
}

bool ListItr::operator!=(ListItr that) const
{
    return (this->m_currNode != that.m_currNode);
}

inline Node* LinkedList::cutHead()
{
    assert(m_size);
    
    Node* removeHead = m_head;
    m_head = m_head->getNext();
    m_size--;

    return removeHead;
}

inline int LinkedList::unbox(Node* const a_node)
{
    assert(a_node);
    int data = a_node->getData();
    delete a_node;

    return data;
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
}

void LinkedList::addLast(int const a_val)
{
    if(isEmpty())
    {
        this->m_head = new Node();
        this->m_head->setData(a_val);
        this->m_head->setNext(m_tail);
    }
    Node* curr = this->m_head;
    while(curr->getNext() != m_tail)
    {
        curr = curr->getNext();
    }
    Node* newTail = new Node();
    newTail->setData(a_val);
    newTail->setNext(m_tail);
    curr->setNext(newTail);
    m_size++;
}

//int LinkedList::remove(int& a_val)
int LinkedList::remove()
{
   return unbox(cutHead());
}

Node* LinkedList::getHead()
{
    return m_head;
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

// bool LinkedList::contains(int a_val) const
// { 
//     Node* a_node = m_head;
//     while(a_node!=NULL)
//     {
//         if(a_node->getData() == a_val)
//         {
//             return true;
//         }
//         a_node = a_node->getNext();
//     }
//     return false;
// }

bool LinkedList::contains(int a_val) const
{ 
    ListItr itr = begin();
    ListItr itrEnd = end();
    while(itr.notEqual(itrEnd))
    {
        if(itr.getData() == a_val)
        {
            return true;
        }
        itr.next();
    }
    return false;
}