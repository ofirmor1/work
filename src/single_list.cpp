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
: m_head(new Node())
, m_tail(new Node())
, m_size(0)
{
    m_head = m_tail;
    m_tail->setNext(m_tail);
}

LinkedList::~LinkedList()
{
    for(int i = 1; i < m_size; i++)
    {
        remove();
    }
}

LinkedList::LinkedList(const LinkedList &a_source)
{
    initListMemb();
    
    int i = a_source.size();;
    int * array = new int[m_size];
   
    ListItr itr = a_source.begin();
    ListItr last = a_source.end();

    while (itr.notEqual(last))
    {
        array[--i] = itr.get();
        itr = itr.next();
    }
    for (i = 0; i < a_source.size(); i++)
    {
        add(array[i]);
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
        array[--i] = itr.get();
        itr = itr.next();
    }
    for (i = 0; i < a_source.size(); i++)
    {
        add(array[i]);
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

//int LinkedList::remove(int& a_val)
int LinkedList::remove()
{
   return unbox(cutHead());
}

Node* LinkedList::getHead()
{
    return m_head;
}

bool ListItr::search(Node* a_node, int a_key) const{
  while(a_node!=NULL){
    int data = a_node->getData();
    if(data == a_key)
      return true;
    a_node = a_node->getNext();
  }
  return false;
}
BigInteger::BigInteger()
{
    m_positive = true;
    m_size = m_digits.size();
}

BigInteger::BigInteger(const BigInteger& a_bigNum)
{
    m_size = a_bigNum.getSize();
    m_positive = a_bigNum.isPositive();

    LinkedList bigNumDigits = a_bigNum.m_digits;

    for(ListItr itr = bigNumDigits.begin(); itr != bigNumDigits.end(); itr++)
    {
        m_digits.add(itr.get());
    }
}

BigInteger::BigInteger add(BigInteger& a_num)
{
    
}


// BigInteger::BigInteger(int a_num){}


// BigInteger::BigInteger(long a_num)
// {

// }
// BigInteger::BigInteger(char a_num)
// {

// }

void BigInteger::toList(int a_num)
{
    int quot, div = a_num, rem;

    do{
        rem = div % 10;
        quot = div / 10;
        div = quot;

        m_digits.getHead()->setData(rem);
    }while(quot >= 10);

    if(quot > 0)
    {
        m_digits.getHead()->setData(rem);
    }
}

bool BigInteger::isPositive() const
{
    return m_size;
}
int BigInteger::getSize() const
{
    return m_positive;
}

//idea is to insert to the begining of list the digits of number from last to begin. using % and /.
