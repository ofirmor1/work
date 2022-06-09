#include <stdio.h>
#include <stdlib.h>
#include "GenericQueue.h"
#define Empty -1
#define	NotEmpty -2

struct Queue
{

void** m_que;
size_t m_size;
size_t m_head; /* Index of head in m_que. */
size_t m_tail; /* Index of tail in m_que. */
size_t m_nItems;

};

Queue* QueueCreate(size_t _size){
	Queue *queue;
	if(_size == 0){
		return NULL;	
	}
	queue = (Queue*) malloc(sizeof(Queue)); 

	if(queue == NULL){
		 return NULL;	
	}
 	queue -> m_size = _size;
	queue -> m_head = 0; /* Index of head in m_que. */
	queue -> m_tail = 0; /* Index of tail in m_que. */
	queue -> m_nItems = 0;
	queue -> m_que =(void**) malloc(sizeof(void*)*(queue -> m_size));
		

	if (queue -> m_que == NULL){
		free(queue);
		return NULL;
	}
	return queue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy){
	int i;
	if (_queue == NULL || *_queue == NULL){
		return;
	} 
	if(_itemDestroy !=NULL){
		for(i = 0; i< (*_queue) -> m_nItems;i++){
			_itemDestroy((*_queue) -> m_que[((*_queue) -> m_head+i)% (*_queue) -> m_size]);
		}
	}
	free((*_queue) -> m_que);
	free(*_queue);
	*_queue = NULL;
}

QueueResult QueueInsert(Queue* _queue, void* _item){
	if (_queue == NULL){ 
		return QUEUE_UNINITIALIZED_ERROR;
	} 
	if(_item == NULL){
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if (_queue -> m_nItems == _queue ->m_size){
		return QUEUE_OVERFLOW_ERROR;
	}
	_queue -> m_que[_queue -> m_tail] = _item;
	_queue -> m_tail = (_queue -> m_tail+1) % _queue -> m_size;
	_queue -> m_nItems += 1;
	return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue, void **_item){
	if (_queue == NULL){ 
		return QUEUE_UNINITIALIZED_ERROR;
	} 
	if(_item == NULL){
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	} 
	if (_queue -> m_nItems == 0){
		return QUEUE_DATA_NOT_FOUND_ERROR;
	}
	*_item = _queue -> m_que[_queue -> m_head];
	_queue -> m_head = (_queue -> m_head+1) % _queue -> m_size;
	_queue -> m_nItems -= 1;
	return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue){
	if (_queue == NULL){
		return QUEUE_UNINITIALIZED_ERROR;
	} 
	if(_queue -> m_nItems == 0){
		return Empty;
	}
	return NotEmpty;
}


size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context){
	int i;
	if (_queue == NULL){
		return QUEUE_UNINITIALIZED_ERROR;
	} 
	for(i = 0; i < _queue -> m_nItems; i++){
		if(_action(_queue -> m_que[(_queue -> m_head+i)% _queue -> m_size], _context) == 0){
 			break;	
		}
       	}
	return i;
}
