#include <cstdio>
#include <cassert>
#include <iostream>
#include "single_list.hpp"

using namespace std;

LinkedList::LinkedList()
: m_head(new Node())
, m_tail(new Node())
, m_size(0)
{
    m_head->m_next = m_tail;
    m_tail->m_next = 0;
}

/*LinkedList::~LinkedList()
{
    assert(!m_head);
    Node* temp;
    while(m_head)
    {
        temp = m_head;
        m_head = m_head->m_next;
        delete[] temp;
        temp = NULL;
    }
    m_head = NULL;
    m_size = 0;
}*/

/*
m_head = NULL;
m_size = 0;
*/
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
        m_head->m_data = nodeCopy->m_data;
        m_head = NULL;
        nodeCopy = nodeCopy->m_next;
        m_size = 1;

        while(nodeCopy != NULL)
        {
            Node* newNode = new Node;
            newNode->m_data = nodeCopy->m_data;
            newNode->m_next = NULL;
            tempNode->m_next = newNode;
            tempNode = tempNode->m_next;
            nodeCopy = nodeCopy->m_next;
            m_size++;
        }

    }
}
LinkedList& LinkedList::operator=(LinkedList const& a_list) 
{
	if (a_list.m_head->m_next != a_list.m_tail)
	{
		Node* temp;
		while (m_head)
		{
			temp = m_head;
			m_head = m_head->m_next;
			delete[] temp;
			temp = NULL;
		}
		initListMemb();
	}
	else
	{
		Node* temp = new Node;
		initListMemb();
		Node* copyhead = a_list.m_head;
		m_head = temp;
		m_head->m_data = copyhead->m_data;
		m_head->m_next = NULL;
		copyhead = copyhead->m_next;
		m_size = 1;

		while (copyhead != NULL) {
			Node* second = new Node;
			second->m_data = copyhead->m_data;
			second->m_next = NULL;
			temp->m_next = second;
			temp = temp->m_next;
			copyhead = copyhead->m_next;
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
        m_head = m_head->m_next;
        delete[] first;
        first = NULL;
        m_size--;
    }
}