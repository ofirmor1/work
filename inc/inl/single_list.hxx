#ifndef SINGLE_LIST_HXX
#define SINGLE_LIST_HXX

#include <iostream>

namespace cpp
{

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

template <typename T>
bool LinkedList<T>::contains(T a_val) const
{ 
    return cpp::contains(*this, a_val);

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

template <typename T>
inline void LinkedList<T>::printList() const
{
    ListItr<T> itr = begin();
    ListItr<T> itrEnd = end();
    while (itr.equal(itrEnd) == false)
    {
        std::cout << itr.getData() << " ";
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
ListItr<T>* ListItr<T>::operator->()
{
    return this;
}

} // namespace name

#endif /*ifndef SINGLE_LIST_HXX*/

