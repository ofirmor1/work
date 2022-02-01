#include <cstdio>
#include <cassert>
#include <iostream>
#include "single_list.hpp"

using namespace std;

ListItr::ListItr()
:m_currNode(new Node()){}

ListItr::ListItr(Node* a_node)
:m_currNode(a_node){}

LinkedList::LinkedList()
: m_head(new Node())
, m_tail(new Node())
, m_size(0)
{
    m_head->setNext(m_tail);
    m_tail->setNext(m_tail);
}

LinkedList::~LinkedList()
{
    for(int i = 1; i < m_size; i++)
    {
        remove();
    }
}

LinkedList::LinkedList(const LinkedList &a_list)
{
    if (a_list.m_head == NULL)
    {
        initListMemb();
    }
    else
    {
        Node* tempNode = new Node;
        initListMemb();
        Node* nodeCopy = a_list.m_head;
        m_head = tempNode;
        m_head->setData(nodeCopy->getData());
        m_head = NULL;
        nodeCopy = nodeCopy->getNext();
        m_size = 1;

        while(nodeCopy != NULL)
        {
            Node* newNode = new Node;
            newNode->setData(nodeCopy->getData());
            newNode->setNext(m_tail);
            tempNode->setNext(newNode);
            tempNode = tempNode->getNext();
            nodeCopy = nodeCopy->getNext();
            m_size++;
        }

    }
}

LinkedList& LinkedList::operator=(LinkedList const& a_list) 
{
	if (a_list.m_head->getNext() != a_list.m_tail)
	{
		Node* temp;
		while (m_head)
		{
			temp = m_head;
			m_head = m_head->getNext();
			delete[] temp;
			temp = NULL;
		}
		initListMemb();
	}
	else
	{
        Node* tempNode = new Node;
        initListMemb();
        Node* nodeCopy = a_list.m_head;
        m_head = tempNode;
        m_head->setData(nodeCopy->getData());
        m_head = NULL;
        nodeCopy = nodeCopy->getNext();
        m_size = 1;

		while (nodeCopy != NULL) 
        {
            Node* newNode = new Node;
            newNode->setData(nodeCopy->getData());
            newNode->setNext(m_tail);
            tempNode->setNext(newNode);
            tempNode = tempNode->getNext();
            nodeCopy = nodeCopy->getNext();
            m_size++;
		}
	}
    
	return *this;
}

//int LinkedList::remove(int& a_val)
void LinkedList::remove()
{
    assert(m_head && m_size);
    if(m_size == 1)
    {
        delete[] m_head;
        m_head = NULL;
        m_size--;
    }
    else
    {
        Node* first = m_head;
        m_head = m_head->getNext();
        delete[] first;
        first = NULL;
        m_size--;
    }
}

int Node::getData()
{
    return m_data;
}

Node* Node::getNext()
{
    return m_next;
}

void Node::setData(int a_val)
{
    m_data = a_val;
}

void Node::setNext(Node* a_node)
{
    m_next = a_node;
}

ListItr ListItr::next()
{
    m_currNode = m_currNode->getNext();
    return ListItr(m_currNode);
}

int ListItr::get()
{
    return m_currNode->getData();
}

ListItr LinkedList::begin() const
{
    ListItr itr = m_head;
    return itr;
}

ListItr LinkedList::end() const
{
    ListItr itr = m_tail;
    return itr;
}

bool ListItr::equals(const ListItr &a_first) const
{
	return a_first == m_currNode;
}