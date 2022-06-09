#include <stdlib.h>
#include "genericDll.h"
#include "listStructs.h"
#define MAGIC_NUMBER 5986
/******************************************************/
List* ListCreate(void)
{
    List *listPtr;
        
        listPtr= (List*) malloc (sizeof(List));
        if(NULL == listPtr)
        {
            return NULL;
        }

        listPtr->m_head.m_prev = &listPtr->m_head;
        listPtr->m_tail.m_next = &listPtr->m_tail;
        listPtr->m_head.m_next = &listPtr->m_tail;
        listPtr->m_tail.m_prev = &listPtr->m_head;
        listPtr->m_magicNumber = MAGIC_NUMBER;
        return listPtr;
}
/******************************************************/
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* current = NULL;
	if (NULL == _pList && NULL == *_pList && (*_pList)->m_magicNumber == MAGIC_NUMBER)
	{
        return;
    }
    current = (*_pList)->m_tail.m_prev;
    while (current->m_prev != NULL)
    {
        current = current->m_prev;
        if (_elementDestroy != NULL)
        {
            _elementDestroy(&current->m_next->m_data);
        }
        free(current->m_next);
    }
    (*_pList)->m_magicNumber = 0;
    free(*_pList);
    *_pList = NULL;
}
/******************************************************/
List_Result InsertBefore(Node* _currNode, void* _item)
{	
	Node* newNode;
	if(NULL == _currNode)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	newNode = malloc(sizeof(Node));
	if(NULL == _item)
	{
		LIST_NULL_ELEMENT_ERROR;
	}
	newNode->m_data = _item;
	newNode->m_prev = _currNode->m_prev;
	newNode->m_next = _currNode;
	_currNode->m_prev->m_next = newNode;
	_currNode->m_prev = newNode;
	
	return LIST_SUCCESS;
}
/******************************************************/
List_Result ListPushHead(List* _list, void* _item)
{
    
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	return InsertBefore(_list->m_head.m_next, _item);
}
/******************************************************/
List_Result ListPushTail(List* _list, void* _item)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}

	return InsertBefore(_list->m_tail.m_prev, _item);;
}
/******************************************************/
List_Result Remove(Node* _nodeToRemove, void** _pItem)
{
	if(NULL == _pItem)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	_nodeToRemove->m_next->m_prev = _nodeToRemove->m_prev;
	_nodeToRemove->m_prev->m_next = _nodeToRemove->m_next;
	*_pItem = _nodeToRemove->m_data;
	free(_nodeToRemove);
	
	return LIST_SUCCESS;
}
/******************************************************/
List_Result ListPopHead(List* _list, void** _pItem)
{
    if(NULL == _list)
    {
        return LIST_UNINITIALIZED_ERROR;
    }
    if(_list->m_head.m_next == &_list->m_tail)
    {
        return LIST_UNDERFLOW_ERROR;
    }
    
    return Remove(_list->m_head.m_next, _pItem);
}
/******************************************************/
List_Result ListPopTail(List* _list, void** _pItem)
{
    Node *temp;
	if(NULL == _list)
    {
        return LIST_UNINITIALIZED_ERROR;
    }
    if(_list->m_head.m_next == &_list->m_tail)
    {
        return LIST_UNDERFLOW_ERROR;
    }	
	
	return Remove(_list->m_tail.m_prev, _pItem);;
}
/******************************************************/
size_t ListSize(const List* _list)
{
    size_t index;
	Node* temp;
	if (NULL == _list)
	{
		return -1;
	}
	temp = _list-> m_head.m_next;
	for (index = 0; temp != &_list->m_tail; index++)
	{
		temp = temp->m_next;
	}
	return index;
}
/******************************************************/
int ListIsEmpty(List* _list)
{
	if (_list == NULL)
	{
		return -1;
	}

	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_IS_EMEPTY_ERROR;
	}
	return LIST_IS_NOT_EMEPTY_ERROR;
}
/* ListPrint is only for debug */
/******************************************************/
/*void ListPrint(List* _list)
{
	Node* temp;
	int index;

	if (NULL == _list)
	{
		return;	
	}
	if(ListIsEmpty(_list) == LIST_IS_EMEPTY_ERROR)
	{
		printf("The list is empty\n");
	}

	temp = _list-> m_head.m_next;
	for (index = 0; temp != &_list->m_tail; index++)
	{
		printf("%d\n",temp->m_data);
		temp = temp->m_next;
	}
	
}*/
/******************************************************/


