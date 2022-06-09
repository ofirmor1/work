    #include <stdlib.h>
#include <stdio.h>
#include "genericVec.h"

struct Vector
{
    void **m_data;
    size_t m_size;
    size_t m_capacity;
};
/***********************************************************/
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
    Vector *vector = malloc(sizeof(Vector));

    if(vector)
    {
        if(!_initialCapacity)
        {
            vector->m_capacity = _initialCapacity + 1;
        }
        else
        {
            vector->m_capacity = _initialCapacity;
        }
        vector->m_size = _initialCapacity;
        vector->m_size = _blockSize;
        vector->m_data =  malloc(sizeof(void*) * _initialCapacity);

        if(!vector->m_data)
        {
            free(vector);
            vector = NULL;
        }
    }

    return vector;
}
/***********************************************************/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
    size_t index;
    if(NULL == _vector)
    {
        return;
    }
    for(index = 0; index < (*_vector)->m_size; index++)
    {  
        _elementDestroy((*_vector)->m_data[index]);
    }
    if(_vector && *_vector) {
        free((*_vector)->m_data);
        free(*_vector);
        *_vector = NULL;
    }
}
/***********************************************************/
void vectorResize(Vector* _vector, size_t _size)
{
    void **data = realloc(_vector->m_data, sizeof(void*) * _size);
    if (data)
    {
        _vector->m_data = data;
        _vector->m_capacity = _size;
    }
}
/***********************************************************/
VectorResult VectorAppend(Vector* _vector, void* _item)
{
    if(!_vector)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if(_vector->m_size >= _vector->m_capacity)
    {
        vectorResize(_vector, _vector->m_capacity * 2);
    }

    _vector->m_data[_vector->m_size++] = _item;

    return VECTOR_SUCCESS;
}
/***********************************************************/
VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
    if(_vector->m_size == 0)
    {
        return VECTOR_UNITIALIZED_ERROR;
    }

    *_pValue = _vector->m_data[--_vector->m_size];

    return VECTOR_SUCCESS;
}
/***********************************************************/
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
    if(_index >= _vector->m_size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    *_pValue = _vector->m_data[_index];

    return VECTOR_SUCCESS;
}
/***********************************************************/
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
    if(_index >= _vector->m_size)
    {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    _vector->m_data[_index] = _value;

    return VECTOR_SUCCESS;
}
/***********************************************************/
size_t VectorSize(const Vector* _vector)
{
	if (NULL == _vector)
	{
		return 0;
	}
    return _vector->m_size;
}
/***********************************************************/
size_t VectorCapacity(const Vector* _vector)
{
	if (NULL == _vector)
	{
		return 0;
	}
    return _vector->m_capacity;
}
/***********************************************************/
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	size_t index;
	void* pValue;

	if(NULL == _vector)
	{
		_context = NULL;
		return -1;
	}

	for (index = 0 ; index< _vector->m_size; index++)
	{
		VectorGet(_vector, index, &pValue);		
		if(_action(pValue, index, _context) == 0)
		{
			break;
		}
	}
    
	return index;
}
/***********************************************************/
void VectorPrint(const Vector *_vector)
{
    size_t index = 0;
    size_t size = vectorGetSize(_vector);

    printf("capacity= %zu\n", _vector->m_capacity);
    printf("size= %zu\n", _vector->m_size );
    printf("data: ");
    for(;index < size; index++)
    {
        printf("%s, ",  (char*)(_vector->m_data[index]));
    }
    printf("\n");
}
/***********************************************************/


int main(void)
{
}
