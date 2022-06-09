#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "HashMap.h"
#include "genericDll.h"
#include "list_functions.h"
#include "list_Itr.h"

#define TRUE 1
#define FALSE 0
#define MAGIC_NUMBER	48934537


struct HashMap
{
	int m_magicNumber;
	size_t m_capacity;
	HashFunction m_hash;
	EqualityFunction m_isEqual;
	size_t m_nElements;
	List** m_listArr;
};

typedef struct
{
	const void* m_key;
	void* m_value;
} Pair;

struct FindAndKey
{
	EqualityFunction m_isEqualOfUser;
	const void* m_key;
};

static size_t PrimeCapacity(size_t _capacity);
static ListItr isFound(const HashMap* _map, const void* _key, size_t hashIndx);


/************************************************************************/
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* map;
	if (NULL == _hashFunc || NULL == _keysEqualFunc || _capacity < 1)
	{
		return NULL;
	}
	map = (HashMap*)malloc(sizeof(HashMap));
	if (map == NULL)
	{
		return NULL;
	}
	map->m_capacity = PrimeCapacity(_capacity);
	map->m_hash = _hashFunc;
	map->m_isEqual = _keysEqualFunc;
	map->m_nElements = 0;
	
	map->m_listArr = (List**)calloc(map->m_capacity, sizeof(List*));
	if (map->m_listArr == NULL)
	{
		free(map);
		return NULL;
	}
	map->m_magicNumber = MAGIC_NUMBER;
	return map;
}
/************************************************************************/
static void DestroyList(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	ListItr it = ListItr_Begin(_list);
	ListItr end = ListItr_End(_list);
	Pair* data;
	while (it != end)
	{
		data = (Pair*)ListItr_Get(it);
		if(_keyDestroy)
		{
			_keyDestroy((void*)data->m_key);
		}
		if(_valDestroy)
		{
			_valDestroy((void*)data->m_value);
		}
		/*free(data);*/
		it = ListItr_Next(it);
	}
	ListDestroy(&_list, NULL);
}
/************************************************************************/
void HashMap_Destroy(HashMap** _map, DestroyFunction _keyDestroy, DestroyFunction _valDestroy)
{
	int i;
	if (NULL == _map || NULL == *_map || (*_map)->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	for (i = 0; i < (*_map)->m_capacity; ++i)
	{
		if((*_map)->m_listArr[i] != NULL)
		{
			DestroyList((*_map)->m_listArr[i], _keyDestroy, _valDestroy);
		}
	}
	free((*_map)->m_listArr);
	(*_map)->m_magicNumber = 0;
	free(*_map);
	*_map = NULL;
}
/************************************************************************/
static Map_Result CheckNull(HashMap* _map, const void* _key, void* _value)
{
	if(_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (_key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if (_value == NULL)
	{
		return MAP_VALUE_NULL_ERROR;
	}
	return MAP_SUCCESS;
}
/************************************************************************/
Map_Result HashMap_Insert(HashMap* _map, const void* _key, void* _value)
{
	size_t hashIndx;
	Pair* pair;
	void* val;
	Map_Result result;
	ListItr end;
	
	result = CheckNull(_map, _key, _value);
	if (result != MAP_SUCCESS)
	{
		return result;
	}

	result = HashMap_Find(_map, _key, &val);
	if (result != MAP_KEY_NOT_FOUND_ERROR)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}

	hashIndx = _map->m_hash(_key) % _map->m_capacity;
	if (NULL == _map->m_listArr[hashIndx])
	{
		_map->m_listArr[hashIndx] = ListCreate();
		if (_map->m_listArr[hashIndx] == NULL)
		{
			return MAP_ALLOCATION_ERROR;
		}
	}

	pair = (Pair*)malloc(sizeof(Pair));
	if (NULL == pair)
	{
		return MAP_ALLOCATION_ERROR;
	}
	pair->m_key = _key;
	pair->m_value = _value;

	end = ListItr_End(_map->m_listArr[hashIndx]);
	ListItr_InsertBefore(end, pair);
	++_map->m_nElements;

	return MAP_SUCCESS;
}
/************************************************************************/
int HashIsEqual(void* _listValue, void* _context)
{
	struct FindAndKey* findInfo = (struct FindAndKey*)_context;
	Pair* current = (Pair*)_listValue;
	return findInfo->m_isEqualOfUser(current->m_key, findInfo->m_key);
}
/************************************************************************/
static ListItr isFound(const HashMap* _map, const void* _key, size_t hashIndx)
{
	ListItr begin, end;
	struct FindAndKey context;
	
	if (NULL == _map->m_listArr[hashIndx])
	{
		return NULL;
	}
	
	context.m_isEqualOfUser = _map->m_isEqual;
	context.m_key = _key;

	begin = ListItr_Begin(_map->m_listArr[hashIndx]);
	end = ListItr_End(_map->m_listArr[hashIndx]);
	return ListItr_FindFirst(begin, end, HashIsEqual, &context);
}
/************************************************************************/
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, const void** _pKey, void** _pValue)
{
	size_t hashIndx;
	ListItr itr, end;
	Pair* pair;
	if(NULL == _map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	hashIndx = _map->m_hash(_searchKey) % _map->m_capacity;
	end = ListItr_End(_map->m_listArr[hashIndx]);
	
	itr = isFound(_map, _searchKey, hashIndx);
	if (ListItr_Equals(itr, end))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	pair = (Pair*)ListItr_Remove(itr);
	--_map->m_nElements;
	*_pValue = pair->m_value;
	*_pKey = pair->m_key;
	free(pair);
	return MAP_SUCCESS;
}
/************************************************************************/
Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
	ListItr itr, end;
	size_t hashIndx;
	
	if (NULL == _map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	hashIndx = _map->m_hash(_key) % _map->m_capacity;
	if(_map->m_listArr[hashIndx])
	{
		itr = isFound(_map, _key, hashIndx);
		end = ListItr_End(_map->m_listArr[hashIndx]);
		if (itr != end)
		{
			*_pValue = ((Pair*)ListItr_Get(itr))->m_value;
			return MAP_SUCCESS;
		}
	}
	return MAP_KEY_NOT_FOUND_ERROR;
}
/************************************************************************/
size_t HashMap_Size(const HashMap* _map)
{
	if (NULL == _map)
	{
		return 0;
	}
	return _map->m_nElements;
}
/************************************************************************/
void HashMap_Print(const HashMap* _map)
{
	int i;
	Pair* pair;
	ListItr begin, end;
	size_t count = 0;
	
	if (NULL == _map)
	{
		return;
	}
	for (i = 0; i < _map->m_capacity; ++i)
	{
		if(_map->m_listArr[i] != NULL)
		{
			begin = ListItr_Begin(_map->m_listArr[i]);
			end = ListItr_End(_map->m_listArr[i]);
			while (begin != end)
			{
				pair = (Pair*)ListItr_Get(begin);
				printf("key: %d \n", *(int*)pair->m_key);
				printf("value: %d \n", *(int*)pair->m_value);
				begin = ListItr_Next(begin);
			}
		}
	}
}

/************************************************************************/
static size_t PrimeCapacity(size_t _capacity)
{
    size_t div, index, primeCapacity = _capacity;
    int isPrime = FALSE;
    while(isPrime)
    {
       isPrime = TRUE;
       for(div = 2; div < sqrt(primeCapacity); div++)
       {
           if((primeCapacity % div) == 0)
           {
                isPrime = FALSE;
                break;
           }
       } 
       if(isPrime == TRUE)
       {
           return primeCapacity;
       }
        primeCapacity++;
    }
    
    return primeCapacity;
}





