#include <stdio.h>
#include <stdlib.h>
#include "VectorGeneric.h"


struct Vector{ 
void **m_items;
size_t m_originalSize; 
size_t m_capacity;
size_t m_size;
size_t m_blockSize;
};

Vector* VectorCreate (size_t _initialSize, size_t _extensionBblockSize){
	Vector *vector;
	if(_initialSize == 0 && _extensionBblockSize == 0){
		return NULL;	
	}
	vector = (Vector*) malloc(sizeof(Vector)); 

	if(vector == NULL){
		 return NULL;	
	}
	vector -> m_originalSize = _initialSize;
	vector -> m_blockSize = _extensionBblockSize;
	vector -> m_size = 0;
	vector -> m_capacity =_initialSize;
	vector -> m_items =(void**) malloc(sizeof(void*)*(_initialSize));
	if (vector -> m_items == NULL){
		free(vector);
		return NULL;
	}
	return vector;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void *_item)){
	int i;
	void *tmp;
	if (_vector == NULL || *_vector == NULL){
		return;
	} 
	if(_elementDestroy !=NULL){
		for(i = 0; i < (*_vector) -> m_size; i++){
			VectorGet(*_vector, i, &tmp);
			(*_elementDestroy)(tmp);
		}
	}
	free(*_vector);
	*_vector = NULL;
}

VectorResult incrementation(Vector *_vector){
	void **tmp;
	tmp = (void*) realloc(_vector->m_items ,sizeof(void*)*(_vector ->m_capacity + _vector -> m_blockSize));
	if(tmp == NULL){
		return VECTOR_ALLOCATION_ERROR;
	}
	_vector->m_items = tmp;
	_vector ->m_capacity = _vector -> m_capacity + _vector -> m_blockSize;
	return VECTOR_SUCCESS;
}

VectorResult VectorAppend(Vector* _vector, void *_item){
	if (_vector == NULL || _item == NULL){
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector -> m_size == _vector -> m_capacity){
		if(_vector -> m_blockSize < 0){
			return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
		}
		if (_vector -> m_blockSize == 0){
			return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
		}
		if(incrementation(_vector) != VECTOR_SUCCESS){
			return VECTOR_ALLOCATION_ERROR;
		}
	}
	_vector -> m_items[_vector -> m_size] = _item;
	_vector -> m_size =_vector -> m_size + 1;
	return VECTOR_SUCCESS;
}

VectorResult discremenation(Vector *_vector){
	void **tmp;
	tmp = (void*) realloc(_vector->m_items,sizeof(void*)* (_vector ->m_capacity - _vector -> m_blockSize));
	if(tmp == NULL){
		return VECTOR_ALLOCATION_ERROR;
	}
	_vector->m_items = tmp;
	_vector ->m_capacity = _vector ->m_capacity - _vector -> m_blockSize;
	return VECTOR_SUCCESS;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue){
	if(_vector == NULL || _pValue == NULL){
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector -> m_size == 0){
		return VECTOR_UNDERFLOW;
	}
	*_pValue = *((_vector -> m_items) + (_vector -> m_size)-1);
	_vector -> m_size = _vector -> m_size - 1;

	if(_vector->m_size > _vector -> m_originalSize &&
	 _vector->m_size - 2 * _vector -> m_blockSize >= _vector -> m_size){
		if(discremenation(_vector) != VECTOR_SUCCESS){
			return VECTOR_ALLOCATION_ERROR;
		}
	}

	return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue){
	if(_vector == NULL ||_pValue == NULL){
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_index >= _vector -> m_size){
		return 	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	*_pValue = _vector -> m_items[_index];
	return VECTOR_SUCCESS;
}


VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value){
	if(_vector == NULL || _value == NULL){
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_index >= _vector -> m_size){
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector -> m_items[_index] = _value;
	return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector){
	if(_vector == NULL ){
		return -1;
	}
 	return _vector -> m_size;
}

size_t VectorCapacity(const Vector* _vector){
	if(_vector == NULL ){
		return -1;
	}
 	return _vector -> m_capacity;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context){
	int i;
	void *elem;
	for(i = 0; i < VectorSize(_vector); i++){
        	VectorGet(_vector, i, &elem);
		if(_action(elem, i, _context) == 0){
 			break;	
		}
       	}
 	return i;
}

