#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkedList.h"
#include "ADTDefs.h"
#define MAGICNUMBER 654654
#define LIST_IS_EMPTY 1
#define LIST_IS_NOT_EMPTY 0


struct Node
{
int m_data;
Node* m_next;
Node* m_prev;
};

struct List
{
Node m_head;
Node m_tail;
int m_magicNumber;
};

/************************************************************************************/
List* ListCreate(void)
{
	List *listPtr;
	
	listPtr= (List*) malloc (sizeof(List));
	if(NULL == listPtr)
	{
		return NULL;
	}

	listPtr->m_head.m_prev = NULL;
	listPtr->m_tail.m_next = NULL;
	listPtr->m_head.m_next = &listPtr->m_tail;
	listPtr->m_tail.m_prev = &listPtr->m_head;
	listPtr->m_magicNumber = MAGICNUMBER;
	return listPtr;
}
/************************************************************************************/
void ListDestroy(List* _list)
{
	Node* temp;
	int i;
	if (_list==NULL || _list->m_magicNumber != MAGICNUMBER)
	{
		return;
	}

	temp=_list->m_head.m_next;
	for (i=0; temp->m_next == &_list->m_tail; i++)
	{
		free(temp);
		temp = temp->m_next;
	}
	
	free(_list);

	_list->m_magicNumber = 0;
}
/************************************************************************************/
ADTErr ListPushHead(List* _list, int _data)
{
	Node* nodePtr;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}

	nodePtr= (Node*) malloc (sizeof(Node));
	if (NULL == nodePtr)
	{
		return ERR_NOT_INITIALIZED;
	}
	nodePtr->m_data = _data;
	nodePtr->m_prev = &_list->m_head;
	nodePtr->m_next = _list->m_head.m_next;
	_list->m_head.m_next->m_prev = nodePtr;
	_list->m_head.m_next = nodePtr;	

	return ERR_OK;
}
/************************************************************************************/
ADTErr ListPushTail(List* _list, int _data)
{
	Node* nodePtr;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}

	nodePtr= (Node*) malloc (sizeof(Node));
	if (NULL == nodePtr)
	{
		return ERR_NOT_INITIALIZED;
	}
	nodePtr->m_data = _data;
	nodePtr->m_next = &_list->m_tail;
	nodePtr->m_prev = _list->m_tail.m_prev;
	_list->m_tail.m_prev->m_next = nodePtr;
	_list->m_tail.m_prev = nodePtr;

	return ERR_OK;
	
}
/************************************************************************************/
ADTErr ListPopHead(List* _list, int* _data) 
{
	Node *temp;

	if(NULL == _list || NULL == _data )
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_LIST_IS_EMPTY;
	}
	

	*_data = _list-> m_head.m_next-> m_data;
	_list-> m_head.m_next = _list->m_head.m_next->m_next;
	_list->m_head.m_next->m_prev = &_list->m_head;
	return ERR_OK;
	
	
}
/************************************************************************************/
ADTErr ListPopTail(List* _list, int* _data) 
{
	Node *temp;

	if(NULL == _list || NULL == _data )
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return ERR_LIST_IS_EMPTY;
	}
	
	*_data = _list->m_tail.m_prev->m_data;
	_list-> m_tail.m_prev = _list->m_tail.m_prev->m_prev;
	_list->m_tail.m_prev->m_prev = &_list->m_tail;
	return ERR_OK;

}
/************************************************************************************/
size_t ListCountItems(List* _list)
{
	size_t i;
	Node* temp;
	if (_list == NULL)
	{
		return -1;
	}
	temp = &_list-> m_head;
	for (i=0; temp->m_next != &_list->m_tail; i++)
	{
		temp = temp->m_next;
	}
	return i;
}
/************************************************************************************/
int ListIsEmpty(List* _list)
{
	if (_list == NULL)
	{
		return -1;
	}

	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_IS_EMPTY;
	}
	return LIST_IS_NOT_EMPTY;
}
/* ListPrint is only for debug */
/************************************************************************************/
void ListPrint(List* _list)
{
	Node* temp;
	int i;

	if (NULL == _list)
	{
		return;	
	}
	if(ListIsEmpty(_list) == LIST_IS_EMPTY)
	{
		printf("The list is empty\n");
	}

	temp = &_list-> m_head;
	temp = temp->m_next;
	for (i=0; temp != &_list->m_tail; i++)
	{
		printf("%d\n",temp->m_data);
		temp = temp->m_next;
	}
	
}
/************************************************************************************/
