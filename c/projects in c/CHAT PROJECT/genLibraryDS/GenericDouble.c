#include "GenericDouble.h"
#include "internalListItr.h"
#include <stdio.h>
#include <stdlib.h>
#define isEmpty 1
#define isNotEmpty 0
/*
struct Node{

void* m_data;
Node* m_next;
Node* m_prev;

};

struct List{

Node m_head;
Node m_tail;

};
*/
Node* NodeCreate(void *_data){
	Node *newNode;
	newNode = (Node*) malloc(sizeof(Node));
	if(newNode == NULL){
		return NULL;
	}
	newNode -> m_data = _data;
	newNode -> m_next = NULL;
	newNode -> m_prev = NULL;
	return newNode;
}

List* ListCreate(void){
	List *myList;
	myList = (List*) malloc(sizeof(List));
	if (myList == NULL){
		return NULL;
	}
	myList -> m_tail.m_next =&myList -> m_tail;
	myList ->m_head.m_prev = &myList -> m_head;
	myList ->m_head.m_next = &myList -> m_tail;
	myList -> m_tail.m_prev = &myList -> m_head;
	return myList;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item)){
	Node *current;
	Node *prev;
	if(_pList == NULL || *_pList == NULL){
		return;
	}
	current = (*_pList) -> m_head.m_next;

	while(current != &(*_pList) -> m_tail){
 		prev = current;
		if(_elementDestroy != NULL){
			_elementDestroy(prev -> m_data);
		}
		current = current ->m_next;
		free(prev);
	}	
	free(*_pList);
	*_pList = NULL;
}


ListResult ListPushHead(List* _list, void* _item){
	Node *newNode;
	if(_list == NULL || _item == NULL){
		return LIST_UNINITIALIZED_ERROR;
	}
	if((newNode = NodeCreate(_item)) == NULL){
		return NODE_ALLOCATION_ERROR;
	}
	newNode -> m_prev = &_list -> m_head;
	newNode -> m_next = _list -> m_head.m_next;
	_list -> m_head.m_next -> m_prev = newNode;
	_list -> m_head.m_next = newNode;
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list, void* _item){
	Node *newNode;
	if(_list == NULL || _item == NULL){
		return LIST_UNINITIALIZED_ERROR;
	}
	if((newNode = NodeCreate(_item)) == NULL){
		return NODE_ALLOCATION_ERROR;
	}
	newNode -> m_next = &_list -> m_tail;
	newNode -> m_prev = _list -> m_tail.m_prev; 
	_list -> m_tail.m_prev -> m_next = newNode;
	_list -> m_tail.m_prev = newNode;
	return LIST_SUCCESS;
}

static int ListIsEmpty(const List* _list){
	if(_list -> m_head.m_next == &_list -> m_tail){
		return isEmpty;
	}
	return isNotEmpty;	
} 

ListResult ListPopHead(List* _list, void** _pItem){
	Node *toPop;
	if(_list == NULL){
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_pItem == NULL){
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(ListIsEmpty(_list) == isEmpty){
		return LIST_UNDERFLOW;
	}
	toPop = _list -> m_head.m_next -> m_next;
	*_pItem = _list -> m_head.m_next -> m_data;
	free(_list -> m_head.m_next);
	_list -> m_head.m_next = toPop;
	_list -> m_head.m_next -> m_prev = &_list -> m_head;
	return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem){
	Node *toPop;
	if(_list == NULL){
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_pItem == NULL){
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(ListIsEmpty(_list) == isEmpty){
		return LIST_UNDERFLOW;
	}
	toPop = _list -> m_tail.m_prev -> m_prev;
	*_pItem = _list -> m_tail.m_prev -> m_data;
	free(_list -> m_tail.m_prev);
	_list -> m_tail.m_prev = toPop;
	_list -> m_tail.m_prev -> m_next = &_list -> m_tail;
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list){
	size_t counter = 0;
	Node *current;
	if(_list==NULL){
		return 0;
	}
	current = _list->m_head.m_next;
	while(current != &_list -> m_tail){
		counter++;
		current = current -> m_next;
	}
	return counter;
}


void ListPrint(List* _list){
	Node *current;
	if(_list==NULL){
		return;
	}
	 current = _list->m_head.m_next;
	
	while(current != &_list -> m_tail){
		printf("%d, ",*(int*)current->m_data);
		current = current -> m_next;
	}		
}


Node* getFirstNode(List* _list){
	return _list -> m_head.m_next;
}

Node* getHeadNode(List* _list){
	return  &_list -> m_head;
}

Node* getLastNode(List* _list){
	return _list -> m_tail.m_prev;
}

Node* getTailNode(List* _list){
	return &_list -> m_tail;
}

Node* getPrevNode(Node* node){
	return node -> m_prev;
}

Node* getNextNode(Node* node){
	return  node -> m_next;
}

void* getNodeValue(Node* node){
	return node -> m_data;
}

