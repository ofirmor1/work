#include "Iterator.h"
#define TRUE 1
#define FALSE 0




ListItr ListItrBegin(const List* _list){
	if(_list == NULL){
		return NULL;
	}
	return (ListItr*)_list -> m_head.m_next;
}

ListItr ListItrEnd(const List* _list){
	if(_list == NULL){
		return NULL;
	}
	return (ListItr*)&_list -> m_tail;
}

int ListItrEquals(const ListItr _a, const ListItr _b){

	if( _a == _b){	
		return TRUE;
	}

	return FALSE;
}

ListItr ListItrNext(ListItr _itr){
	if(_itr == NULL){
		return NULL;
	}
	return (ListItr*)((Node*) _itr) -> m_next;
}

ListItr ListItrPrev(ListItr _itr){
	if(_itr == NULL){
		return NULL;
	}
	if(((Node*)_itr) -> m_prev == ((Node*)_itr) -> m_prev -> m_prev){
		return _itr;
	}
	return (ListItr*)((Node*) _itr) -> m_prev;
}

void* ListItrGet(ListItr _itr){
	if(_itr == NULL){
		return NULL;
	}
	if((Node*)_itr == ((Node*)_itr) -> m_next){
		return  NULL;
	}
	return ((Node*)_itr) -> m_data;
}

void* ListItrSet(ListItr _itr, void* _element){
	void *deleteElem;
	if(_itr == NULL || _element == NULL){
		return NULL;
	}
	if((Node*)_itr == ((Node*)_itr) -> m_next){
		return NULL;
	}
	deleteElem = ((Node*)_itr) -> m_data;
	((Node*)_itr) -> m_data = _element;

	return deleteElem;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element){
	Node *newNode;
	if(_itr == NULL || _element == NULL){
		return NULL;
	}
 	newNode = NodeCreate(_element);
	if(newNode == NULL){
		return NULL;
	}
	newNode -> m_next = (Node*)_itr;
	newNode -> m_prev = ((Node*)_itr) -> m_prev;
	((Node*)_itr) -> m_prev -> m_next = newNode;
	((Node*)_itr) -> m_prev = newNode;

	return (ListItr*)newNode;
}

void* ListItrRemove(ListItr _itr){
	void *toRemove;
	if(_itr == NULL){
		return NULL;
	}
	toRemove = ((Node*)_itr) -> m_data;
	((Node*)_itr) -> m_prev ->m_next = ((Node*)_itr) -> m_next;
	((Node*)_itr) -> m_next -> m_prev = ((Node*)_itr) -> m_prev;
	free((Node*)_itr);
	return toRemove;
}



