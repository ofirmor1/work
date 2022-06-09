#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "ADTDefs.h"
#include "vector.h"
#define FATHER(i) (i-1)/2
#define LEFT_SON(i) (i*2)+1
#define RIGHT_SON(i) (i*2)+2
heapa->m_compare
struct Heap
{
	void** m_heap;
	/*Vector* m_vec;*/
	size_t m_heapSize;
	int (*compare)(void* a, void* b);
	/*LessThanComparator comparator;*/
};
/*
static int IsLeaf(Heap* _heap, int _indx);
static int GetBiggest(Heap* _heap, int _indx);
static void swap(Heap* _heap, int _indx, int _big);
static void BubbleUp(Heap* _heap, int _data);
*/
/********************** heapify  ***************************************/
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	Heap *pHeap;
	size_t index = 0;
	if(_vector == NULL){
		return NULL;
	}
	pHeap = (Heap*)malloc(sizeof(Heap));
	if(pHeap == NULL){	
		return NULL;
	pHeap->m_vec = _vector;
   	pHeap->m_heapSize = VectorSize(_vector);
 	pHeap->m_lessThan = _pIfLess;
	index = FATHER(pHeap->m_heapSize - 1);
	while(index >= 0){
		Heapify(pHeap, index);
		index--;
	}   	
	return pHeap;
}
/***********************************************************************/
Vector* HeapDestroy(Heap** _heap)
{
	if(_heap == NULL)
	{
		return NULL;
	}
	free(_heap);
	_heap = NULL;
	return *_heap;
}

/***********************************************************************/

static void BubbleUp(Heap* _heap)
{
	void* father,leftSon;
	size_t index = _heap->m_heapSize - 1;
	VectorGet(_heap->m_vec, FATHER(index), &father);
	VectorGet(_heap->m_vec, LEFT_SON(index), &father);
	while(index >= 0 && _heap->compare(father, leftSon) > 0))
	{ 
	 	VectorSet(_heap->m_vec, index, father);
	 	VectorSet(_heap->m_vec, FATHER(index), son);
		index = FATHER(index);
		VectorGet(_heap->m_vec, FATHER(index), &father);
	}
}
/***********************************************************************/
HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
	HeapResultCode result;
	if(_heap == NULL || _element == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	result = VectorAdd (_heap -> m_vector , _element);
	if( result != VECTOR_SUCCESS)
	{
		return result;
	}
	_heap -> m_heapSize++;
	bubbleUp(_heap);
	
	return HEAP_SUCCESS;
}
/***********************************************************************/
const void* HeapPeek(const Heap* _heap)
{
	void* peak;
	if(NULL == _heap)
	{
		return;
	}
	VectorGet(_heap->m_vec, 0 , &peak);
	if(_heap->m_heapSize > 0)
	{
		return peak;
	}
	return;
}
/***********************************************************************/
void* HeapExtract(Heap* _heap)
{
	int eror;
	if(NULL == _heap)
	{
		return;
	}
	if(_heap->m_heapSize == 0){
		return;
	}
	eror = VectorGet(_heap->m_vec, 0, _data); 
	return eror;
}
/***********************************************************************/
size_t HeapSize(const Heap* _heap)
{
	if(NULL == _heap)
	{
		HEAP_NOT_INITIALIZED;
	}
	return _heap->m_heapSize;
}

/***********************************************************************/
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t index, item;
	if(NULL == _heap || NULL == _act)
	{
		return;
	}
	for(index = 1, index < _heap->m_heapSize, index++)
	{
		VectorGet(_heap->m_vec, index, &item);
		if(_act(item, _context) == 0)
		{
			break;
		}
	}
	return index;
}
/***********************************************************************/
void HeapSort(Vector* _vec, LessThanComparator _pfLess)
{
	for(index = 1, index < _heap->m_heapSize, index++)
	{
		VectorGet(_heap->m_vec, index, &item);
		VectorGet(_heap->m_vec, index, &item);
		if(_ptLess(item, _context) == 0)
		{
			break;
		}
	}
}

/***********************************************************************/
static int IsLeaf(Heap* _heap, int _indx)
{	
	if(LEFT_SON(_indx) < _heap->m_heapSize)
	{
		return FALSE;
	}
	return TRUE;
}
/***********************************************************************/
static int GetBiggest(Heap* _heap, int _indx)
{
	int left, right, father, bigValue, bigIndx;
	VectorGet(_heap->m_vec, _indx, &father);
	VectorGet(_heap->m_vec, LEFT_SON(_indx), &left);
	bigValue = father;
	bigIndx = _indx;
	
	if(RIGHT_SON(_indx) < _heap->m_heapSize)
	{    /*if right isn't a leaf*/
		VectorGet(_heap->m_vec, RIGHT_SON(_indx), &right);
		bigValue = (father > right) ? father : right;		
		bigIndx = (father > right) ? _indx : RIGHT_SON(_indx);
	}	
	bigIndx = (bigValue > left) ? bigIndx : LEFT_SON(_indx);
	return bigIndx;
}
/***********************************************************************/
static void swap(Heap* _heap, int _indx, int _big)
{
	int father, son;
	VectorGet(_heap->m_vec, _big, &father);
	VectorGet(_heap->m_vec, _indx, &son);
	VectorSet(_heap->m_vec, _indx, father); 
	VectorSet(_heap->m_vec, _big, son); 
}
/***********************************************************************/
void Heapify(Heap* _heap, int _indx)
{
	int bigIndx;
	if(IsLeaf(_heap, _indx) == TRUE)
	{
		return;
	}
	bigIndx = GetBiggest(_heap, _indx);
	if(bigIndx != _indx)
	{
		swap(_heap, _indx ,bigIndx);
		Heapify(_heap, bigIndx);
	}
	
}
/***********************************************************************/
int HeapItemsNum(Heap* _heap)
{
	if(NULL == _heap)
	{
		return 0;
	}
	
	return _heap->m_heapSize;
}
/***********************************************************************/
void HeapPrint(Heap* _heap)
{
	if(NULL == _heap)
	{
		return;
	}
	VectorPrint(_heap->m_vec);
}













