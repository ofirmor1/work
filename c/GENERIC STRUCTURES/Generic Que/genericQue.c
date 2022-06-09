#include <stdlib.h>	
#include "genericQue.h"


struct Queue

{

void** m_que;

size_t m_size;

size_t m_head; /* Index of head in m_que. */

size_t m_tail; /* Index of tail in m_que. */

size_t m_nItems;


};
/***********************************************************/
Queue* QueueCreate(size_t _size)
{
	Queue* ptrQueue;

	if (_size == 0)
	{
		return NULL;
	}
	ptrQueue = (Queue*)malloc(sizeof(Queue));
	if(NULL == ptrQueue)
	{
		return NULL;
	}
	ptrQueue->m_que= (void**)malloc(sizeof(void*)*_size);
	if(NULL == ptrQueue->m_que)
	{
		free(ptrQueue);
		return NULL;
	}

	ptrQueue->m_size =_size;
	ptrQueue->m_head = 0;
	ptrQueue->m_tail = 0;
	ptrQueue->m_nItems = 0;
	return ptrQueue;
}
/***********************************************************/
void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t index;
    if(NULL == _queue)
    {
        return;
    }		
	for(index; index < (*_queue)->m_nItems ;index = (index + 1) % ((*_queue)->m_size))
    {  
        _itemDestroy((*_queue)->m_que[index]);
    }
    if(_queue && *_queue) 
	{
        free((*_queue)->m_que);
        free(*_queue);
        *_queue = NULL;
    }
}
/***********************************************************/
QueueResult QueueInsert(Queue* _queue,void* _item)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}

	if(_queue->m_nItems == _queue->m_size)
	{
		return QUEUE_OVERFLOW_ERROR;
	}

	*(_queue->m_que + _queue->m_tail) = _item;
	_queue->m_tail=(_queue->m_tail+1)%_queue->m_size;
	_queue->m_nItems++;

	return QUEUE_SUCCESS;
}
/***********************************************************/
QueueResult QueueRemove(Queue* _queue,void** _item)
{
	if(NULL == _queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;

	}
	if(NULL==_item)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}

	if(_queue->m_nItems == 0)
	{
		return QUEUE_DATA_NOT_FOUND_ERROR;  
	}
	
	*_item= *(_queue->m_que + _queue->m_head);
	_queue->m_head=(_queue->m_head+1)%_queue->m_size;
	_queue->m_nItems--;

	return QUEUE_SUCCESS;
}
/***********************************************************/
size_t QueueIsEmpty(Queue* _queue)
{
	if(NULL == _queue)
	{
		return 0;
	}

	if(_queue->m_nItems == 0)
	{
		return 1;
	}	
	return 0;
}

/***********************************************************/
size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	size_t index;
	int count = 0;
	if(NULL == _queue || NULL == _action)
	{
		_context = NULL;
		return -1;
	}

	index = _queue->m_head;
		
	for(index; count < (_queue->m_nItems) ;index = (index + 1) % (_queue->m_size))
	{	
		if(_action(_queue->m_que[index], _context) == 0)
		{
			break;
		}
		count++;
	}
    
	return index;
}
/***********************************************************/
