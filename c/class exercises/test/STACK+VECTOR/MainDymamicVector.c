#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Vector.h"
#include "ADTDefs.h"

/*Vector *VectorCreate(size_t _initialSize, size_t _extentionBblockSize)*/
/*given size 5, blocksize 3 - not NULL.*/
void CheckCreateNull ()
{
	size_t initialSize=10;
	size_t extentionBblockSize=2;

	if( VectorCreate(initialSize,extentionBblockSize)!=NULL)
	{
		printf("CheckCreateNull-pass\n");
		return;
	}
	printf("CheckCreateNull-fail\n");
	
}


/*****************************************************************************/
/* if size == blocksize == 0, return NULL*/

void CheckCreateSize0Blocksize0 ()
{
	size_t initialSize=0;
	size_t extentionBblockSize=0;
	if(VectorCreate(initialSize,extentionBblockSize)==NULL)
	{
		printf("CheckCreateSize0Blocksize0- pass\n");
		return;
	}
	printf("CheckCreateSize0Blocksize0- fail\n");
}

/*****************************************************************************/
/*if size !=0 && blocksize ==0 - not NULL*/

void CheckCreateSizeNot0Blocksize0 ()
{
	size_t initialSize=3;
	size_t extentionBblockSize=0;
	if(VectorCreate(initialSize,extentionBblockSize)!=NULL)
	{
		printf("CheckCreateSizeNot0Blocksize0- pass\n");
		return;
	}
	printf("CheckCreateSizeNot0Blocksize0- fail\n");
}

/*****************************************************************************/
/*size == 0 && blocksize != 0 - not NULL*/
void CheckCreateSize0BlockSizeNot0 ()
{
	size_t initialSize=0;
	size_t extentionBblockSize=3;
	if(VectorCreate(initialSize,extentionBblockSize)!=NULL)
	{
		printf("CheckCreateSize0BlockSizeNot0- pass\n");
		return;
	}
	printf("CheckCreateSize0BlockSizeNot0- fail\n");

}

/*****************************************************************************/

/*if malloc_fail - return NULL. (size==-1, for ex.)*/
void CheckCreateSizeUder0 ()
{
	size_t initialSize = -1;
	size_t extentionBblockSize = 3;
	if(VectorCreate(initialSize,extentionBblockSize)==NULL)
	{
		printf("CheckCreateSizeUder0- pass\n");
		return;
	}
	printf("CheckCreateSizeUder0- fail\n");

}

/*****************************************************************************/

 /*if _vector !=NULL, check that destroy works*/
void CheckDestroy ()
{	
	size_t initialSize=2;
	size_t extentionBblockSize=3;
	Vector * ptrVector;

	ptrVector = VectorCreate(initialSize,extentionBblockSize);
	VectorDestroy(ptrVector);
	printf("CheckDestroyBasic pass\n");
	return;
}
/*****************************************************************************/
void CheckDestroyNULL ()
{	

	VectorDestroy(NULL);
	printf("CCheckDestroyNULL pass\n");
	return;
}
/*****************************************************************************/
/*create & 2 * destroy - check that*/
void CheckDDestroy ()
{	
	size_t initialSize=2;
	size_t extentionBblockSize=3;
	Vector * ptrVector;

	ptrVector = VectorCreate(initialSize,extentionBblockSize);
	VectorDestroy(ptrVector);
	VectorDestroy(ptrVector);	
	printf("CheckDDestroy pass\n");
	return;
}

/*****************************************************************************/
/*check that NULLs if _vector==NULL.*/
/*VectorAdd(Vector* _vector, int _item)*/

void CheckAddNULL ()
{
	if(VectorAdd(NULL, 3)==ERR_NOT_INITIALIZED)
	{
		printf("CheckAddNULL-pass\n");
	}
	else
	{	
		printf("CheckAddNULL-Fail\n");
	}	
}

/*****************************************************************************/
/* if room in m_size - just insert int and get expected result
	a. _vector->m_items[_vector->m_nItems-1] == _item*/


void CheckAddItem () 
{
	Vector * ptrVector;

	ptrVector = VectorCreate(3,2);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	VectorAdd(ptrVector, 3);
	if(getn(ptrVector,  2)==3)
	{
		printf("CheckAddItem-pass\n");
	}
	else
	{
		printf("CheckAddItem-fail\n");
	}

}

/*****************************************************************************/
/* numOfItems==numOfItems+1*/

void CheckAddNumOfItems () 
{
	Vector * ptrVector;

	ptrVector = VectorCreate(3,2);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	VectorAdd(ptrVector, 3);
	if(Getm_nItems(ptrVector)==3)
	{
		printf("CheckAddNumOfItems-pass\n");
	}
	else
	{
		printf("CheckAddNumOfItems-fail\n");
	}

}
/*****************************************************************************/
/*no room in m_size - check for overflow err - blocksize==0 */
void CheckAddOverflow () 
{
	Vector * ptrVector;

	ptrVector = VectorCreate(1,0);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	if (VectorAdd(ptrVector, 3)== ERR_OVERFLOW)
	{
		printf("CheckAddOverflow-pass\n");
	}
	else
	{
		printf("CheckAddOverflow-fail\n");
	}

}


/*****************************************************************************/
/*no room in m_size realloc err - ;*/

void CheckAddReallocate () 
{
	Vector * ptrVector;

	ptrVector = VectorCreate(1,1);
	VectorAdd(ptrVector, 1);
	if (VectorAdd(ptrVector, 2)!= ERR_REALLOCATION_FAILED)
	{
		printf("CheckAddReallocate-pass\n");
	}
	else
	{
		printf("CheckAddReallocate-fail\n");
	}

}

/*****************************************************************************/
/*no room in m_size _vector->m_size=+blocksize*/

void CheckAddReallocateSize () 
{
	Vector * ptrVector;

	ptrVector = VectorCreate(1,1);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	if (Getm_size (ptrVector)==2)
	{
		printf("CheckAddReallocate-pass\n");
	}
	else
	{
		printf("CheckAddReallocate-fail\n");
	}

}	



/*****************************************************************************/
/*NULLs if _vector==NULL. */

void CheckDeleteVectorIsNull ()
{
	int i;
	if(VectorDelete (NULL, &i)==ERR_NOT_INITIALIZED)
	{
		printf("CheckDeleteVectorIsNull-pass\n");
	}
	else 
	{
		printf("CheckDeleteVectorIsNull-fail\n");
	}


}

/*****************************************************************************/

/*NULLs if _item==NULL.*/ 
void CheckDeleteItemIsNull ()
{
	Vector * ptrVector;

	ptrVector = VectorCreate(2,3);
	
	if(VectorDelete (ptrVector, NULL)==ERR_NOT_INITIALIZED)
	{
		printf("CheckDeleteItemIsNull-pass\n");
	}
	else 
	{
		printf("CheckDeleteItemIsNull-fail\n");
	}

}

/*****************************************************************************/
/*delete that's supposed to -blocksize from m_size - works.*/

void CheckDeleteSizeDecBlocksize ()
{
	Vector * ptrVector;
	int i;
	size_t sizeBeforeRealloc;

	ptrVector = VectorCreate(3,1);

	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);

	sizeBeforeRealloc = Getm_size (ptrVector);
	
	VectorDelete (ptrVector, &i);
	VectorDelete (ptrVector, &i);
	
	if(Getm_size (ptrVector)== sizeBeforeRealloc-1)
	{
		printf("CheckDeleteSizeDecBlocksize-pass\n");
	}
	else 
	{
		printf("CheckDeleteSizeDecBlocksize-fail\n");
	}	
}
/*****************************************************************************/
/*m_size cannot become < m_original_size.*/
void CheckDeleteSizeBigOrEqualToOriginalSize ()
{
	Vector * ptrVector;
	int i;
	size_t sizeBeforeRealloc;

	ptrVector = VectorCreate(3,1);

	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);
	VectorAdd(ptrVector, 3);
	
	VectorDelete (ptrVector, &i);
	VectorDelete (ptrVector, &i);
	VectorDelete (ptrVector, &i);
	
	if(Getm_size (ptrVector)>=Getm_originalSize (ptrVector) )
	{
		printf("CheckDeleteSizeBigOrEqualToOriginalSize-pass\n");
	}
	else 
	{
		printf("CheckDeleteSizeBigOrEqualToOriginalSize-fail\n");
	}	
}

/*****************************************************************************/
/*5. if no need for realloc - just delete int and get expected result*/
/*a. *_item = *((_vector->m_items)+(_vector->m_nItems)-1);*/

void CheckDeleteItemValue ()
{
	Vector * ptrVector;
	int i;
	size_t sizeBeforeRealloc;

	ptrVector = VectorCreate(5,1);

	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	VectorAdd(ptrVector, 3);

	VectorDelete (ptrVector, &i);
	
	if(i==3)
	{
		printf("CheckDeleteItemValue-pass\n");
	}
	else 
	{
		printf("CheckDeleteItemValue-fail\n");
	}	
}

/*****************************************************************************/
/*5. if no need for realloc - just delete int and get expected result*/
/*b. numOfItems==numOfItems+1****/
void CheckDeleteNumOfItems ()
{
	Vector * ptrVector;
	int i;
	size_t numOfItems;

	ptrVector = VectorCreate(5,1);

	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 2);
	VectorAdd(ptrVector, 3);
	numOfItems= Getm_nItems (ptrVector);
	VectorDelete (ptrVector, &i);
	
	if(numOfItems-1 == Getm_nItems (ptrVector))
	{
		printf("CheckDeleteNumOfItems-pass\n");
	}
	else 
	{
		printf("CheckDeleteNumOfItems-fail\n");
	}	
}

/*****************************************************************************/
/*if vector->m_size > _vector->m_originalSize
	UNDERFLOW err - numOfElements ==0; (one too many deletes)*/
void CheckDeleteUnderflow ()
{
	Vector * ptrVector;
	int i;

	ptrVector = VectorCreate(5,1);
	
	
	if(VectorDelete (ptrVector, &i) == ERR_UNDERFLOW)
	{
		printf("CheckDeleteUnderflow-pass\n");
	}
	else 
	{
		printf("CheckDeleteUnderflow-fail\n");
	}	
}


/*****************************************************************************/
/*NULLs if _vector==NULL.*/
/*VectorGet(Vector *_vector, size_t _index, int* _item)*/
void GetVectorNull ()
{
	int i;
	if(VectorGet(NULL, 1, &i) == ERR_NOT_INITIALIZED)
	{
		printf("GetVectorNull-pass\n");	
	}
	else 
	{
		printf("GetVectorNull-fail\n");
	}

}

/*****************************************************************************/
/*2. NULLs if _item==NULL. */
/*VectorGet(Vector *_vector, size_t _index, int* _item)*/
void GetItemNull ()
{
	Vector * ptrVector;

	ptrVector = VectorCreate(2,3);
	if(VectorGet(ptrVector, 1, NULL) == ERR_NOT_INITIALIZED)
	{
		printf("GetItemNull-pass\n");	
	}
	else 
	{
		printf("GetItemNull-fail\n");
	}

}

/*****************************************************************************/
/*3. _index = m_nItems - ERR_WRONG_INDEX*/

void GetIndexEqualToNItems ()
{
	Vector * ptrVector;
	int i;

	ptrVector = VectorCreate(2,3);
	VectorAdd(ptrVector, 3);	
	if(VectorGet(ptrVector, 1, &i) == ERR_WRONG_INDEX)
	{
		printf("GetIndexEqualToNItems-pass\n");	
	}
	else 
	{
		printf("GetIndexEqualToNItems-fail\n");
	}
}

/*****************************************************************************/
/*4. _index < m_nItems*/

void GetIndexSmallerThanToNItems ()
{
	Vector * ptrVector;
	int i;

	ptrVector = VectorCreate(2,3);
	VectorAdd(ptrVector, 3);
	VectorGet(ptrVector, 1, &i);	
	if (i==3)
	{
		printf("GetIndexBigThanToNItems-pass\n");	
	}
	else 
	{
		printf("GetIndexBigThanToNItems-fail\n");
	}
}

/********************************Set***********************************************/

/*1. NULLs if _vector==NULL. */
/*VectorSet(Vector *_vector, size_t _index, int _item)*/

void SetCheckNull ()
{
	if(VectorSet(NULL, 1, 2)==ERR_NOT_INITIALIZED)
	{
		printf("SetCheckNull-pass\n");
	}
	else
	{
		printf("SetCheckNull-fail\n");
	}
	
}
/*****************************************************************************/
/*2. _index = m_nItems - ERR_WRONG_INDEX*/

void SetIndexEqualToNItems ()
{
	Vector * ptrVector;
	int item;

	ptrVector = VectorCreate(2,3);
	VectorAdd(ptrVector, 3);	
	if(VectorSet(ptrVector, 1, item) == ERR_WRONG_INDEX)
	{
		printf("SetIndexEqualToNItems-pass\n");	
	}
	else 
	{
		printf("SetIndexEqualToNItems-fail\n");
	}
}
	

/*****************************************************************************/
/*3. _index < m_nItems*/

void SetIndexSmallerThanToNItems ()
{
	Vector * ptrVector;
	int i;

	ptrVector = VectorCreate(2,3);
	VectorAdd(ptrVector, 3);
	VectorGet(ptrVector, 1, &i);	
	if (i==3)
	{
		printf("SetIndexSmallerThanToNItems-pass\n");	
	}
	else 
	{
		printf("SetIndexSmallerThanToNItems-fail\n");
	}
}

/******************************VectorItemsNum*********************************/
/*1. NULLs if _vector==NULL. */
/*VectorItemsNum(Vector* _vector, size_t* _numOfItems)*/

void ItemsNumCheckVectorIsNull ()
{
	size_t *i;	
	if (VectorItemsNum(NULL, i)== ERR_NOT_INITIALIZED)
	{
		printf("ItemsNumCheckVectorIsNull-pass\n");	
	}
	else 
	{
		printf("ItemsNumCheckVectorIsNull-fail\n");
	}
}

/*****************************************************************************/
/*2. NULLs if numOfItems==NULL. */
/*VectorItemsNum(Vector* _vector, size_t* _numOfItems)*/

void ItemsNumCheckItemIsNull ()
{
	Vector * ptrVector;

	ptrVector = VectorCreate(2,3);	
	if (VectorItemsNum(ptrVector, NULL)== ERR_NOT_INITIALIZED)
	{
		printf("ItemsNumCheckItemIsNull-pass\n");	
	}
	else 
	{
		printf("ItemsNumCheckItemIsNull-fail\n");
	}
}

/*****************************************************************************/
/*3. insert / delete and check idf get right NumOfItems.*/

void ItemsNumCheckIsWorking ()
{
	Vector * ptrVector;
	size_t i;

	ptrVector = VectorCreate(2,3);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 1);
	VectorAdd(ptrVector, 1);
		
	if (VectorItemsNum(ptrVector, &i)== 3)
	{
		printf("ItemsNumCheckIsWorking-pass\n");	
	}
	else 
	{
		printf("ItemsNumCheckIsWorking-fail\n");
	}
}
/*****************************************************************************/


int main (void)
{
	CheckCreateNull ();
	CheckCreateSize0Blocksize0 ();
	CheckCreateSizeNot0Blocksize0 ();
	CheckCreateSize0BlockSizeNot0 ();
	CheckCreateSizeUder0 ();
	CheckDestroy ();
	CheckDestroyNULL ();
	CheckDDestroy ();
	CheckAddNULL ();
	CheckAddItem ();
	CheckAddNumOfItems ();
	CheckAddOverflow ();
	CheckAddReallocate ();
	CheckAddReallocateSize ();
	CheckDeleteVectorIsNull ();
	CheckDeleteItemIsNull ();
	CheckDeleteSizeDecBlocksize ();
	CheckDeleteSizeBigOrEqualToOriginalSize ();
	CheckDeleteItemValue ();
	CheckDeleteNumOfItems ();
	CheckDeleteUnderflow ();
	GetVectorNull ();
	GetItemNull ();
	GetIndexEqualToNItems ();
	GetIndexSmallerThanToNItems ();
	SetCheckNull ();
	SetIndexEqualToNItems ();
	SetIndexSmallerThanToNItems ();
	ItemsNumCheckVectorIsNull ();
	ItemsNumCheckItemIsNull ();
	ItemsNumCheckIsWorking ();
}



/*	Vector* vectorPtr;
	size_t initialSize, extentionBblockSize;
	int item=4;
	int item2=5;
	int i;
	ADTErr underflow;
	size_t index=1;
	size_t numOfItems;
	
	initialSize=5;
	extentionBblockSize=2;

	vectorPtr= VectorCreate(initialSize,extentionBblockSize);
	/*underflow=VectorDelete (vectorPtr, &i);
	printf("underflow=%d\n",underflow);
	VectorAdd(vectorPtr, item);
	/*VectorDelete (vectorPtr, &i);
	printf("i=%d\n",i);
	VectorAdd(vectorPtr, item);
	VectorGet(vectorPtr, index, &i);
	printf("i=%d\n",i);
	VectorItemsNum(vectorPtr, &numOfItems);
	printf("numOfItems=%ld\n",numOfItems);
	VectorSet(vectorPtr, index, item2);
	VectorGet(vectorPtr, index, &i);
	printf("i=%d\n",i);*/
	


