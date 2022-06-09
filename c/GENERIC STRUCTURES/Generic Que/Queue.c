#include <stdio.h>
#include <stddef.h>/*size_t*/
#include <stdlib.h> /* realloc, malloc, size_t*/
#include "Queue.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 1172354



struct Queue

{

int* m_que;

size_t m_size;

size_t m_head; /* Index of head in m_que. */

size_t m_tail; /* Index of tail in m_que. */

size_t m_nItems;

int m_magicNumber;

};


/*************************Create*************************************/

Queue* QueueCreate (size_t _size)
{
	Queue* ptrQueue;

	if (_size==0)
	{
		return NULL;
	}

	ptrQueue=(Queue*)malloc(sizeof(Queue));
	if(NULL==ptrQueue)
	{
		return NULL;
	}
	
	ptrQueue->m_que= (int*)malloc(sizeof(int)*_size);
		if(NULL==ptrQueue->m_que)
	{
		free(ptrQueue);
		return NULL;
	}


	ptrQueue->m_size=_size;
	ptrQueue->m_head=0;
	ptrQueue->m_tail=0;
	ptrQueue->m_nItems=0;
	ptrQueue->m_magicNumber = MAGIC_NUMBER;

	return ptrQueue;
}

/*************************Destroy*************************************/

void QueueDestroy(Queue *_queue)
{
	if(NULL==_queue || _queue->m_magicNumber!= MAGIC_NUMBER)
	{
		return;
	}

	_queue->m_magicNumber=0;
	free(_queue->m_que);
	free(_queue);
		
}
	
/***************************Insert*************************************/
ADTErr QueueInsert (Queue *_queue, int _item)
{
	
	if(NULL==_queue)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(_queue->m_nItems == _queue->m_size)
	{
		return ERR_OVERFLOW;
	}

	*(_queue->m_que + _queue->m_tail)=_item;
	_queue->m_tail=(_queue->m_tail+1)%_queue->m_size;
	_queue->m_nItems++;

	return ERR_OK;
	
}

/***************************Remove*************************************/
ADTErr QueueRemove (Queue *_queue, int *_item)
{
	if(NULL==_queue || NULL==_item)
	{
		return ERR_NOT_INITIALIZED;
	}

	if(_queue->m_nItems == 0)
	{
		return ERR_UNDERFLOW;  
	}
	
	*_item= *(_queue->m_que + _queue->m_head);
	_queue->m_head=(_queue->m_head+1)%_queue->m_size;
	_queue->m_nItems--;

	return ERR_OK;
	
}

/***************************QueueIsEmpty***********************************/

int QueueIsEmpty(Queue *_queue)
{
	if(NULL==_queue)
	{
		return 0;
	}

	if(_queue->m_nItems==0)
	{
		return 1;
	}	
	return 0;

}

/***********************************Print***********************************/

void QueuePrint(Queue *_queue)
{
	int count=0;
	int index;
	if(NULL==_queue)
	{
		return;
	}
	index= _queue->m_head;
		
	for(index; count<(_queue->m_nItems) ;index=(index+1)%(_queue->m_size))
	{
		printf("%d, ",*(_queue->m_que + index));
		count++;
	} 
	printf("\n");
}

size_t GetNumberOfElements(Queue *_queue)
{
	return _queue->m_nItems;
}



/*****************************************************************************/

size_t GetTailValue(Queue *_queue)
{

	return _queue->m_tail;
	
}


size_t GetHeadValue(Queue *_queue)
{

	return _queue->m_head;
	
}

