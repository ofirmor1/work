#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>


using namespace std;

/*******************************INLINE LINKED LIST FUNCS**********************/
inline void LinkedList::printList() const
{
    ListItr itr = begin();
    ListItr itrEnd = end();
    while(itr.equal(itrEnd) == false)
    {
        cout << itr.getData() << endl;
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


inline ListItr LinkedList::begin() const
{
    return (ListItr)m_head;
}

inline ListItr LinkedList::end() const
{
    return (ListItr)m_tail;
}

inline int LinkedList::size() const
{
    return m_size;
}

inline bool LinkedList::isEmpty() const
{
    return m_size == 0;
}
/*******************************INLINE NODE FUNCS**********************/
inline int Node::getData()
{
    return m_data;
}

inline Node* Node::getNext()
{
    return m_next;
}

inline void Node::setData(int a_val)
{
    m_data = a_val;
}

inline void Node::setNext(Node* a_node)
{
    m_next = a_node;
}
/*******************************INLINE LIST_ITERATOR FUNCS**********************/
inline ListItr ListItr::next()
{
    m_currNode = m_currNode->getNext();
    return ListItr(m_currNode);
}

inline int ListItr::getData()
{
    return m_currNode->getData();
}

inline void ListItr::setData(int a_val)
{
    return m_currNode->setData(a_val);
}

inline bool ListItr::equal(const ListItr &a_other) const
{
	return a_other.m_currNode == m_currNode;
}

inline bool ListItr::notEqual(const ListItr &a_other) const
{
	return !equal(a_other);
}

#endif /*ifndef SINGLE_LIST_HXX*/
