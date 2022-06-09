#include "GenericHeap.h"
#include <stdlib.h>
#include "VectorGeneric.h"
#define LEFT(I) (2*(I)+1)
#define RIGHT(I) (2*(I)+2)
#define PARENT(I) ((I-1)/2)
#define TRUE 1
#define FALSE 0
#define MAGIC 31558640
#define EMPTY

struct Heap
{

Vector* m_vec;
size_t m_heapSize;
int magic_number;
LessThanComparator m_comparator;

};


void SwapHeap(Heap* _heap, size_t a, size_t b){
	void *swapA, *swapB;
	VectorGet(_heap -> m_vec, a, &swapA);
	VectorGet(_heap -> m_vec, b, &swapB);
	VectorSet(_heap -> m_vec, b, swapA);
	VectorSet(_heap -> m_vec, a, swapB);
}

static int isLeaf(Heap* _heap, size_t index){

	if (LEFT(index) < _heap -> m_heapSize){
		return FALSE;
	}
	return TRUE;
}

static size_t BigIdx(Heap* _heap, size_t index){
	void *left, *right, *curr;
	int compareCR, compareCL,compareLR;
	VectorGet(_heap -> m_vec, index, &curr);
	VectorGet(_heap -> m_vec, LEFT(index), &left);

	if(RIGHT(index) >= _heap -> m_heapSize){
		if(_heap -> m_comparator(curr, left) == 1){
			return LEFT(index);
		}
		else{
			return index;
		}
	}
	VectorGet(_heap -> m_vec, RIGHT(index), &right);
	compareCR = _heap -> m_comparator(curr, right);
	compareCL = _heap -> m_comparator(curr, left);
	compareLR = _heap -> m_comparator(left, right);
	/*case the father is biggest*/
	if(compareCR == 0 && compareCL == 0){
		return index; 
	}/*case the right is biggest*/
	if(compareCR == 1 && compareLR == 1){
		return RIGHT(index);
	}/*case the left is biggest*/
	else{
		return LEFT(index);
	}
}

void heapify(Heap* _heap,size_t index){
	size_t BigIndex;
	if(isLeaf(_heap, index) == TRUE){
		return;
	}
	BigIndex = BigIdx(_heap, index);
	if(BigIndex != index){
		SwapHeap(_heap,BigIndex, index);
		heapify(_heap, BigIndex);
	}	
}

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess){
	size_t currIdx;
	size_t size;
	Heap *myHeap;
	if(_vector == NULL || _pfLess == NULL){
		return NULL;
	}
	
	myHeap = (Heap*) malloc(sizeof(Heap));
	if (myHeap == NULL){
		return NULL;
	}
	myHeap -> m_vec = _vector;
	size = VectorSize(_vector);
	myHeap -> m_heapSize = size;
	myHeap -> magic_number = 31558640;
	myHeap -> m_comparator = _pfLess;
	for(currIdx = myHeap -> m_heapSize; currIdx >= 0 ; currIdx --){
		heapify(myHeap, currIdx);
		if(currIdx == 0){
			break;	
		}
	}

	return myHeap;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element){
	void *currData;
	size_t i;
	if(_heap == NULL || _element == NULL){
		return HEAP_NOT_INITIALIZED;
	}

	if(VectorAppend(_heap -> m_vec, _element) !=VECTOR_SUCCESS){
		return HEAP_NOT_INITIALIZED;
	}
	_heap -> m_heapSize = _heap -> m_heapSize + 1;
	i = _heap -> m_heapSize-1;
	VectorGet(_heap -> m_vec, PARENT(i), &currData);
	while((_heap -> m_comparator(currData, _element) == 1) && i != 0){
		SwapHeap(_heap ,PARENT(i) ,i);
		i = PARENT(i);
		VectorGet(_heap -> m_vec, PARENT(i), &currData);
	}

	return HEAP_SUCCESS;
}


size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context){
	void *curr;
	size_t i;
	if(_heap == NULL || _act == NULL){
		return 0;
	}
	for(i = 0; i < _heap -> m_heapSize ;i++){	
		VectorGet(_heap ->m_vec, i, &curr);	
		if(_act((const*)curr, _context) == 0){
			break;
		}
	}
	return i;
}


const void* HeapPeek(const Heap* _heap){
	void *data;
	if(_heap == NULL || _heap -> m_heapSize == 0){
		return NULL;
	}
	VectorGet(_heap -> m_vec, 0, data);
	return data;
}

void* HeapExtract(Heap* _heap){
	void *max;
	if(_heap == NULL){
		return NULL;
	}
	SwapHeap(_heap, 0, _heap -> m_heapSize-1);
	if(VectorRemove(_heap ->m_vec, &max) != VECTOR_SUCCESS){
		return NULL;
	}
	_heap -> m_heapSize = _heap -> m_heapSize - 1;
	heapify(_heap,0);
	return max;
}


Vector* HeapDestroy(Heap** _heap){
	Vector *vecToReturn;
	if(_heap == NULL || *_heap == NULL){
		return;
	}
	vecToReturn = (*_heap) -> m_vec;
	/*free((*_heap) -> m_vec);*/
	free(*_heap);
	*_heap = NULL;
	return vecToReturn;
}

size_t HeapSize(const Heap* _heap){
	if(_heap == NULL){
		return EMPTY;
	}
	return _heap -> m_heapSize;
}


