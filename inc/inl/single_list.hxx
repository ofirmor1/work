#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>


using namespace std;

/*******************************INLINE LINKED LIST FUNCS**********************/
template <typename T>
inline void LinkedList<T>::printList() const
{
    ListItr<T> itr = begin();
    ListItr<T> itrEnd = end();
    while(itr.equal(itrEnd) == false)
    {
        cout << itr.getData() << " ";
        itr.next();
    }
}


// inline void LinkedList::add(int const a_val)
// {
//     Node* newNode = new Node(a_val, m_head);
//     m_head = newNode;
//     if(isEmpty())
//     {
//         newNode->setNext(m_tail);
//     }
//     m_size++;
// }

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
/*******************************INLINE NODE FUNCS**********************/
template <typename T>
inline T Node<T>::getData()
{
    return m_data;
}

template <typename T>
inline Node<T>* Node<T>::getNext()
{
    return m_next;
}

template <typename T>
inline void Node<T>::setData(T a_val)
{
    m_data = a_val;
}
template <typename T>
inline void Node<T>::setNext(Node* a_node)
{
    m_next = a_node;
}
/*******************************INLINE LIST_ITERATOR FUNCS**********************/
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

#endif /*ifndef SINGLE_LIST_HXX*/
