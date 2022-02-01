#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>


using namespace std;

/*INLINE FUNCTIONS*/

inline void LinkedList::initListMemb()
{
    m_head->setNext(m_tail);
    m_tail->setNext(m_tail);
    m_size = 0;
}

inline void LinkedList::printList() const
{
    ListItr itr = begin();
    ListItr itrEnd = end();
    while(itr.equals(itrEnd) == false)
    {
        cout << itr.get() << endl;
        itr.next();
    }
}

// inline void LinkedList::printList() const
// {
//     Node* curr = this->m_head;
//     while(curr->getNext() != this->m_tail)
//     {
//         cout << curr->getData() << endl;
//         curr = curr->getNext();
//     }
// }

inline void LinkedList::add(int a_val)
{
    Node* newNode = new Node;
    newNode->setData(a_val);    
    newNode->setNext(m_head);
    m_head = newNode;
    m_size++;
}

inline int LinkedList::size() const
{
    return m_size;
}

inline bool LinkedList::isEmpty() const
{
    return m_size == 0;
}
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

inline ListItr ListItr::next()
{
    m_currNode = m_currNode->getNext();
    return ListItr(m_currNode);
}

inline int ListItr::get()
{
    return m_currNode->getData();
}

inline ListItr LinkedList::begin() const
{
    return ListItr(m_head);
}

inline ListItr LinkedList::end() const
{
    return ListItr(m_tail);
}

inline bool ListItr::equals(const ListItr &a_first) const
{
	return a_first.m_currNode == m_currNode;
}

#endif /*ifndef SINGLE_LIST_HXX*/
