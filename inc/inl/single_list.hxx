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

// inline void LinkedList::printList() const
// {
//     ListItr itr = begin();
//     ListItr itrEnd = end();
//     while(ListItrEquals(itr,itrEnd))
//     {
//         cout << itr.get() << endl;
//         itr.next();
//     }
// }

inline void LinkedList::printList() const
{
    Node* curr = this->m_head;
    while(curr->getNext() != this->m_tail)
    {
        cout << curr->getData() << endl;
        curr = curr->getNext();
    }
}

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

#endif /*ifndef SINGLE_LIST_HXX*/
