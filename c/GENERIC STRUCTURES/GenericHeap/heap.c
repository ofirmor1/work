#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "ADTDefs.h"
#include "vector.h"
#define MAGIC_NUMBER 5553364
#define FATHER(i) (i-1)/2
#define LEFT_SON(i) (i*2)+1
#define RIGHT_SON(i) (i*2)+2

struct Heap{

	Vector* m_vec;
	size_t m_heapSize;
	int m_magicNumber;
};
/*
static int IsLeaf(Heap* _heap, int _indx);
static int GetBiggest(Heap* _heap, int _indx);
static void swap(Heap* _heap, int _indx, int _big);
static void BubbleUp(Heap* _heap, int _data);
*/
/********************** heapify  ***************************************/
static int IsLeaf(Heap* _heap, int _indx){	
	if(LEFT_SON(_indx) < _heap->m_heapSize){
		return FALSE;
	}
	return TRUE;
}

static int GetBiggest(Heap* _heap, int _indx){
	int left, right, father, bigValue, bigIndx;
	VectorGet(_heap->m_vec, _indx, &father);
	VectorGet(_heap->m_vec, LEFT_SON(_indx), &left);
	bigValue = father;
	bigIndx = _indx;
	
	if(RIGHT_SON(_indx) < _heap->m_heapSize){    /*if right isn't a leaf*/
		VectorGet(_heap->m_vec, RIGHT_SON(_indx), &right);
		bigValue = (father > right) ? father : right;		
		bigIndx = (father > right) ? _indx : RIGHT_SON(_indx);
	}	
	bigIndx = (bigValue > left) ? bigIndx : LEFT_SON(_indx);
	return bigIndx;
}

static void swap(Heap* _heap, int _indx, int _big){
	int father, son;
	VectorGet(_heap->m_vec, _big, &father);
	VectorGet(_heap->m_vec, _indx, &son);
	VectorSet(_heap->m_vec, _indx, father); 
	VectorSet(_heap->m_vec, _big, son); 
}
/*iterative Heapify*/
/*void Heapify(Heap* _heap, int _indx){
	int father, son, bigIndx;	
	while(IsLeaf(_heap, LEFT_SON(_indx)) == FALSE){
		bigIndx = GetBiggest(_heap, _indx);
		if(bigIndx == _indx){
			break;
		}
		swap(_heap, _indx ,bigIndx);
		_indx = bigIndx;
	}
}*/
/*Recursive Heapify*/
void Heapify(Heap* _heap, int _indx){
	int bigIndx;
	if(IsLeaf(_heap, _indx) == TRUE){
		return;
	}
	bigIndx = GetBiggest(_heap, _indx);
	if(bigIndx != _indx){
		swap(_heap, _indx ,bigIndx);
		Heapify(_heap, bigIndx);
	}
	
}
/***********************************************************************/
Heap* HeapBuild(Vector* _vec){
   	Heap *pHeap;
   	int i;
   	if(_vec == NULL){
   		return NULL;
   	}
   	pHeap = (Heap*)malloc(sizeof(Heap));
   	if(pHeap == NULL){	
   		return NULL;
   	}
   	pHeap->m_vec = _vec;
   	VectorItemsNum(_vec, &(pHeap->m_heapSize));
   	pHeap-> m_magicNumber = MAGIC_NUMBER;  	
   	i = FATHER(pHeap->m_heapSize - 1);
   	while(i >= 0){
   		Heapify(pHeap, i);
   		i--;
   	}   	
	return pHeap;
}

/***********************************************************************/

void HeapDestroy(Heap* _heap){
	if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER){
		return;
	}
	_heap->m_magicNumber = 0;
	free(_heap);
}
/***********************************************************************/

static void BubbleUp(Heap* _heap, int _data){ /*change to index!*/
	int father, son = _data;
	size_t i = _heap->m_heapSize - 1;
	VectorGet(_heap->m_vec, FATHER(i), &father);
	
	while(i >= 0 && son > father){ 
	 	VectorSet(_heap->m_vec, i, father);
	 	VectorSet(_heap->m_vec, FATHER(i), son);
		i = FATHER(i);
		VectorGet(_heap->m_vec, FATHER(i), &father);
	}
}

ADTErr HeapInsert(Heap* _heap, int _data){
	int eror;
	if(_heap == NULL){
		return ERR_NOT_INITIALIZED;
	}
	eror = VectorAdd(_heap->m_vec, _data);
	if(eror != ERR_OK){
		return eror;
	}
	_heap->m_heapSize++;
	if(_heap->m_heapSize > 1){
		BubbleUp(_heap, _data);
	}	
	return eror;
}
/***********************************************************************/

ADTErr HeapMax(Heap *_heap, int *_data){
	int eror;
	if(_heap == NULL || _data == NULL || _heap->m_magicNumber != MAGIC_NUMBER){
		return ERR_NOT_INITIALIZED;
	}
	if(_heap->m_heapSize == 0){
		return ERR_UNDERFLOW;
	}
	eror = VectorGet(_heap->m_vec, 0, _data); 
	return eror;
}
/***********************************************************************/

ADTErr HeapExtractMax(Heap *_heap, int *_data){
	int eror, last;
	if(_heap == NULL || _data == NULL ||_heap->m_magicNumber != MAGIC_NUMBER){
		return ERR_NOT_INITIALIZED;
	}
	if(_heap->m_heapSize == 0){
		return ERR_UNDERFLOW;
	}
	VectorGet(_heap->m_vec, 0, _data);
	VectorDelete(_heap->m_vec, &last);
	_heap->m_heapSize--;
	VectorSet(_heap->m_vec, 0, last);
	Heapify(_heap, 0);           
	return ERR_OK;
}
/***********************************************************************/

int HeapItemsNum(Heap* _heap){
	if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER){
		return 0;
	}
	return _heap->m_heapSize;
}


/***********************************************************************/
void HeapPrint(Heap* _heap){
	if(_heap == NULL || _heap->m_magicNumber != MAGIC_NUMBER){
		return;
	}
	VectorPrint(_heap->m_vec);
}













