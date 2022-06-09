#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "ADTDefs.h"
#include "vector.h"
#define FATHER(i) (i-1)/2
#define LEFT_SON(i) (i*2)+1
#define RIGHT_SON(i) (i*2)+2
struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	Comparator m_lessThan;
};

/*################### internal functions #############################*/
static int IsLeaf(Heap* _heap, int _indx);
static int GetBiggest(Heap* _heap, int _indx);
static void swap(Heap* _heap, int _indx, int _big);
static void BubbleUp(Heap* _heap, int _data);
void Heapify(Heap* _heap, size_t _indx);
*/
/********************** heapify  ***************************************/
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	Heap *pHeap;
	int index = 0;
	if(_vector == NULL){
		return NULL;
	}
	pHeap = (Heap*)malloc(sizeof(Heap));
	if(pHeap == NULL)
	{	
		return NULL;
	}
	pHeap->m_vec = _vector;
	pHeap->m_heapSize = VectorSize(_vector);
	pHeap_m_lessThan = _pIfLess;
	index = FATHER(pHeap->m_heapSize - 1);
	while(index >= 0)
	{
		Heapify(pHeap, i);
		if(index == 0)
		{
			break;
		}
		index--;
	}   	
	return pHeap;
}
/***********************************************************************/
Vector* HeapDestroy(Heap** _heap)
{
	Vector *pVec;
	if(NULL == _heap || NULL == *_heap)
	{
		return NULL;
	}
	pVec = (*_heap)->m_vec;
	free(*_heap);
	*_heap = NULL;
	return *_heap;
}

/***********************************************************************/
HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
	VectorResult result;
	if(_heap == NULL || _element == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	result = VectorAdd (_heap -> m_vector , _element);
	if( result != VECTOR_SUCCESS)
	{
		return HEAP_APPEND_FAILED;
	}
	_heap -> m_heapSize++;
	bubbleUp(_heap);
	
	return HEAP_SUCCESS;
}
/***********************************************************************/
const void* HeapPeak(const Heap* _heap)
{
	void* peak;
	if(NULL == _heap || _heap->m_heapSize == 0)
	{
		return NULL;
	}
	VectorGet(_heap->m_vec, 0 , &peak);
	return peak;
}
/***********************************************************************/
void* HeapExtract(Heap* _heap)
{
	void *last, *item
	if(NULL == _heap || _heap->m_heapSize == 0)
	{
		return NULL;
	}
	if(_heap->m_heapSize == 0){
		return;
	}
	VectorGet(_heap->m_vec, 0, &item);
	VectorRemove(_heap->m_vec, &last);
	_heap->m_heapSize--;
	if(_heap->m_heapSize > 0)
	{
		VectorSet(_heap->m_vec, 0, last);
		Heapify(_heap, 0);
	}
	return item;
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
	size_t index;
	void* item;
	if(NULL == _heap || NULL == _act)
	{
		return 0;
	}
	for(index = 0, index < _heap->m_heapSize, index++)
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
	size_t index;
	Heap* pHeap;
	if(NULL == _vec)
	{
		return;
	}
	pHeap = HeapBuild(_vec, pIfLess);
	for(index = 0, index < pHeap->m_heapSize, index++)
	{
		swap(pHeap, 0, pHeap->m_heapSize-1);
		pHeap->m_heapSize--;
		Heapify(pHeap, 0);
}

/***********************************************************************/
static int IsLeaf(Heap* _heap, size_t _index)
{	
	if(LEFT_SON(_index) < _heap->m_heapSize)
	{
		return FALSE;
	}
	return TRUE;
}
/***********************************************************************/
static int GetBiggest(Heap* _heap, size_t _index)
{
	void *left, *right, *father, *bigValue;
	size_t bigIndex;
	VectorGet(_heap->m_vec, _index, &father);
	VectorGet(_heap->m_vec, LEFT_SON(_index), &left);
	bigValue = father;
	bigIndx = _index;
	
	if(RIGHT_SON(_index) < _heap->m_heapSize)
	{    /*if right isn't a leaf*/
		VectorGet(_heap->m_vec, RIGHT_SON(_index), &right);
		bigValue = (father > right) ? father : right;		
		bigIndex = (father > right) ? _index : RIGHT_SON(_indx);
	}	
	bigIndex = (bigValue > left) ? bigIndex : LEFT_SON(_index);
	return bigIndx;
}
/***********************************************************************/
static void swap(Heap* _heap, size_t _indx, size_t _big)
{
	void *father, *son;
	VectorGet(_heap->m_vec, _big, &father);
	VectorGet(_heap->m_vec, _indx, &son);
	VectorSet(_heap->m_vec, _indx, father); 
	VectorSet(_heap->m_vec, _big, son); 
}
/***********************************************************************/
void Heapify(Heap* _heap, int _index)
{
	size_t bigIndx;
	if(IsLeaf(_heap, _indx) == TRUE)
	{
		return;
	}
	bigIndx = GetBiggest(_heap, _index);
	if(bigIndx != _index)
	{
		swap(_heap, _index ,bigIndex);
		Heapify(_heap, bigIndex);
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
/***********************************************************************/
static void BubbleUp(Heap* _heap)
{
	void* father,Son;
	size_t index = _heap->m_heapSize - 1;
	VectorGet(_heap->m_vec, FATHER(index), &father);
	VectorGet(_heap->m_vec, LEFT_SON(index), &father);
	while(index > 0 && _heap->compare(father, son) > 0))
	{ 
	 	VectorSet(_heap->m_vec, index, father);
	 	VectorSet(_heap->m_vec, FATHER(index), son);
		index = FATHER(index);
		VectorGet(_heap->m_vec, FATHER(index), &father);
	}
}












