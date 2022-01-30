#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>
#include <single_list.hpp>

using namespace std;

/*INLINE FUNCTIONS*/

inline void LinkedList::initListMemb()
{
    m_head->m_next = m_tail;
    m_tail->m_next = 0;
    m_size = 0;
}

inline void LinkedList::printList() const
{
    Node* curr = this->m_head;
    while(curr->m_next != this->m_tail)
    {
        cout << curr->m_data << endl;
        curr = curr->m_next;
    }
}

inline void LinkedList::add(int a_val)
{
    Node* first = new Node;
    first->m_data = a_val;
    first->m_next = m_head;
    m_head = first;
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
