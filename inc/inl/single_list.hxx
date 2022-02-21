#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>

using namespace std;

template <typename T>
inline void LinkedList<T>::printList() const
{
    ListItr<T> itr = begin();
    ListItr<T> itrEnd = end();
    while (itr.equal(itrEnd) == false)
    {
        cout << itr.getData() << " ";
        itr.next();
    }
}

template <typename T>
inline ListItr<T> LinkedList<T>::begin() const
{
    return (ListItr<T>)m_head;
}

template <typename T>
inline ListItr<T> LinkedList<T>::end() const
{
    return (ListItr<T>)m_tail;
}

template <typename T>
inline size_t LinkedList<T>::size() const
{
    return m_size;
}

template <typename T>
inline bool LinkedList<T>::isEmpty() const
{
    return m_size == 0;
}

template <typename T>
inline T Node<T>::getData()
{
    return m_data;
}

template <typename T>
inline Node<T> *Node<T>::getNext()
{
    return m_next;
}

template <typename T>
inline void Node<T>::setData(T a_val)
{
    m_data = a_val;
}
template <typename T>
inline void Node<T>::setNext(Node *a_node)
{
    m_next = a_node;
}

template <typename T>
inline ListItr<T> ListItr<T>::next()
{
    m_currNode = m_currNode->getNext();
    return ListItr(m_currNode);
}

template <typename T>
inline T ListItr<T>::getData()
{
    return m_currNode->getData();
}

template <typename T>
inline void ListItr<T>::setData(T a_val)
{
    return m_currNode->setData(a_val);
}

template <typename T>
inline bool ListItr<T>::equal(const ListItr &a_other) const
{
    return a_other.m_currNode == m_currNode;
}

template <typename T>
inline bool ListItr<T>::notEqual(const ListItr &a_other) const
{
    return !equal(a_other);
}

//Prefix
template <typename T>
ListItr<T>& ListItr<T>::operator++()
{
    if(m_currNode)
    {
        m_currNode = m_currNode->getNext();
    }

    return *this;
}

//Postfix
template <typename T>
ListItr<T> ListItr<T>::operator++(T)
{
    ListItr it = *this;
    ++*this;
    return it;
}

template <typename T>
bool ListItr<T>::operator==(const ListItr& a_that)
{
    return !operator!=(a_that);
}

template <typename T>
bool ListItr<T>::operator!=(const ListItr& a_that)
{
    return this->m_currNode != a_that.m_currNode;
}

template <typename T>
int ListItr<T>::operator*() const
{
    return m_currNode->getData();
}

template <typename T>
Node<T>* ListItr<T>::operator->() const
{
    return m_currNode;
}



#endif /*ifndef SINGLE_LIST_HXX*/
