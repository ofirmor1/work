#include <stddef.h>
#include "Vector.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 12445



struct Vector 
{
	int* m_items;
	size_t m_originalSize;
	size_t m_size;
	size_t m_nItems;
	size_t m_blockSize;
	int m_magicNumber;
	
};

/***********************************************************************/
Vector *VectorCreate(size_t _initialSize, size_t _extentionBblockSize) 
{

	Vector *ptrStruct;
	int *ptrArray;

		if(_initialSize==0 && _extentionBblockSize==0)
	{
		return NULL;
	}
	

	ptrStruct= (Vector*) malloc(sizeof(Vector));
	ptrArray= (int*) malloc(sizeof(int)*_initialSize);
	if (NULL == ptrStruct || NULL == ptrArray)
	{
		if(	ptrStruct!= NULL)
		{
			free(ptrStruct);
		}
		else
		{
			free(ptrArray);
		}	
		return NULL;
			
	}	


	
	ptrStruct->m_nItems = 0;
	ptrStruct->m_items = ptrArray;
	ptrStruct->m_originalSize = _initialSize;
	ptrStruct->m_size = _initialSize;
	ptrStruct->m_blockSize = _extentionBblockSize;
	ptrStruct->m_magicNumber=MAGIC_NUMBER;
	
	return ptrStruct;
}
/*****************************************************************/

void VectorDestroy(Vector* _vector)
{	
	if((_vector==NULL )|| _vector->m_magicNumber!=MAGIC_NUMBER)
	{
		return;
	}
	
	_vector->m_magicNumber=0;
	free(_vector->m_items);
	free(_vector);
}

/*****************************************************************/

ADTErr VectorAdd(Vector* _vector, int _item)
{	

	size_t AddSize;
	int CurrentSize;
	size_t NewSize;
	size_t OldSize;
	int* temp;

	if(NULL==_vector)
	{
		return ERR_NOT_INITIALIZED;
	}

	AddSize = _vector->m_blockSize;
	OldSize=_vector->m_size;
	NewSize=AddSize+OldSize;
	

		if(_vector->m_size == _vector->m_nItems)
		{
			
			if(AddSize==0)
			{
				return ERR_OVERFLOW;
			}			
			temp= (int*) realloc(_vector->m_items,NewSize*sizeof(int));
			if(NULL==temp)
			{
				return ERR_REALLOCATION_FAILED;		
			}
			_vector->m_items=temp;
			_vector->m_size=NewSize;
				
		}
	
	*(_vector->m_items + _vector->m_nItems)=_item;
	(_vector->m_nItems)++;
	return ERR_OK;
	
}

/*****************************************************************/


ADTErr VectorDelete (Vector* _vector, int* _item)
{
	int* temp;
	if(NULL==_vector ||NULL==_item )
	{
		return ERR_NOT_INITIALIZED;
	}

	if(_vector->m_nItems==0)
	{
			return ERR_UNDERFLOW;				
	}
	
	*_item= *(_vector->m_items + _vector->m_nItems-1); 
	(_vector->m_nItems)--;


	if(_vector->m_originalSize < _vector->m_size &&  _vector->m_size - _vector->m_nItems >=  _vector->m_blockSize*2)
	{
			temp= (int*) realloc(_vector->m_items,(_vector->m_size-_vector->m_blockSize)*sizeof(int));
			if(NULL!=temp)
			{
				_vector->m_items=temp;
				_vector->m_size -= _vector->m_blockSize ;
						
			}
	}
	return ERR_OK;
	
	
}

/*****************************************************************/


ADTErr VectorGet(Vector *_vector, size_t _index, int* _item)
{	
	if (NULL==_vector || NULL==_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_index>=_vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	
	*_item=*(_vector->m_items+_index);
	return ERR_OK;
}

/*****************************************************************/


ADTErr VectorItemsNum(Vector* _vector, size_t* _numOfItems)
{	
	if (NULL==_vector || NULL==_numOfItems)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_numOfItems=_vector->m_nItems;
	return ERR_OK;
}

/*****************************************************************/

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if (NULL==_vector)
	{
		return ERR_NOT_INITIALIZED;
	}

	if (_index>=_vector->m_nItems )/*define rang of number between to 0 to numOfElements*/
	{
		return ERR_WRONG_INDEX;
	}
	
	*(_vector->m_items+_index)= _item;
	return ERR_OK;
	

}

/*****************************************************************/


int Getm_originalSize (Vector* _vector)
{
	return _vector -> m_originalSize;
} 

size_t Getm_size (Vector* _vector)
{
	return _vector -> m_size;
}
 
size_t Getm_nItems (Vector* _vector)
{
	return _vector -> m_nItems;
} 

size_t Getm_blockSize (Vector* _vector)
{
	return _vector -> m_blockSize;
} 

int getn(Vector*_vector,  int i)
{
	return _vector -> m_items[i];
}






