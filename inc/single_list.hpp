#ifndef SINGLE_LIST
#define SINGLE_LIST

#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "single_list.hpp"
// #include "hash_set.hpp"

namespace cpp
{

template <typename T>
class Node
{
public:
    Node();
    Node(T a_data, Node* a_next);
    T getData();
    Node* getNext();
    void setData(T a_val);
    void setNext(Node* a_node);

private:
    T m_data;
    Node* m_next; 
};

template <typename T>
class ListItr: public std::iterator<std::input_iterator_tag, int>
{

public:
    ListItr();
    ListItr(Node<T>* a_node);

    T getData();
    void setData(T a_val);
    ListItr next();

    bool equal(const ListItr<T> &a_other) const;
    bool notEqual(const ListItr<T> &a_other) const;

    ListItr& operator=(Node<T>* a_node);

    ListItr& operator++();
    ListItr operator++(T);

    bool operator==(const ListItr& a_that);
    bool operator!=(const ListItr& a_that);

    int operator*() const;
    ListItr* operator->();

private:
    Node<T>* m_currNode;
};

//SingleLinkedList
template <typename T>
class LinkedList
{

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &a_list);
    LinkedList& operator=(LinkedList const& a_list);

    void addFirst(T const& a_val);
    void addLast(T const& a_val);

    T remove();
    ListItr<T> begin() const;
    ListItr<T> end() const;
    T first() const;
    T last() const;

    size_t size() const;
    bool isEmpty() const;
    void printList() const;
    bool contains(T a_val) const;
    
    LinkedList intersection(LinkedList<T> const& a) const;

    void initListMemb();

private:
    void axioms() const;
    Node<T>* cutHead();
    T unbox(Node<T>* const a_node);

private:
    Node<T>* m_sentinal;
    Node<T>* m_head;
    Node<T>* m_tail;
    int m_size;
};

template <typename T>
bool contains(LinkedList<T> const& a_list, T a_val);
template <typename T>
bool contains(ListItr<T> a_begin, ListItr<T> const a_end , T a_val);
    
} // namespace cpp

#include "single_list.hxx"

#endif /*SINGLE_LIST*/
