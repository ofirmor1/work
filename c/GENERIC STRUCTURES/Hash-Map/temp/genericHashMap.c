#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genericHashMap.h"
#include "list_Itr.h"
#include "list_functions.h"
#include "genericDll.h"
#define MAGIC_NUMBER 79534

#define TRUE 0
#define FALSE 1

struct HashMap
{
    List** m_listArr;
	size_t m_capacity;
    size_t m_nElements;
	HashFunction m_hash;
	EqualityFunction m_isEqual;
	int m_magicNumber;
};

typedef struct Pair
{
	const void* m_key;
	void* m_value;
}Pair;

typedef struct FindKey
{
    const void* m_key;
    EqualityFunction m_compare;
}FindKey;

/******************************************************/
/*******************inner Functions********************/
/******************************************************/
static size_t PrimeCapacity(size_t _capacity);
static void Destroy_List(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
static Map_Result CheckNull(HashMap* _map, const void* _key, void* _value);
int IsEqualKeys(void *_hashKey, void *_keyToFind);
static ListItr isFound(const HashMap* _map, const void* _key, size_t _hashIndx);
/******************************************************/
/********************API Functions*********************/
/******************************************************/
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* map;
    if(_capacity < 1 || NULL == _hashFunc || NULL == _keysEqualFunc)
    {
        return NULL;
    }
    map = (HashMap*)malloc(sizeof(HashMap));
    if(NULL == map)
    {
        return NULL;
    }
	map->m_capacity = PrimeCapacity(_capacity);
    map->m_nElements = 0;
	map->m_hash = _hashFunc;
	map->m_isEqual = _keysEqualFunc;
    map->m_listArr = (List**)calloc(map->m_capacity, sizeof(List*));
    if(NULL == map->m_listArr)
    {
        free(map);
        return NULL;
    }
    map->m_magicNumber = MAGIC_NUMBER;
    
    return map; 
}
/************************************************************************/
static void Destroy_List(List* _list, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    ListItr itr = ListItr_Begin(_list);
    ListItr endOfList = ListItr_End(_list);
    Pair* pair;
    while(itr != endOfList)
    {
        pair = (Pair*)ListItr_Get(itr);
        if(_keyDestroy)
        {
            _keyDestroy(pair->m_key);
        }
        if(_valDestroy)
        {
            _valDestroy(pair->m_value);
        }
        free(pair);
        itr = ListItr_Next(itr);
    }
    ListDestroy(&_list, NULL);
}

/************************************************************************/
void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    int index;
    if(NULL == _map || NULL == *_map || (*_map)->m_magicNumber != MAGIC_NUMBER)
    {
        return;
    }
    for(index = 0; index < (*_map)->m_capacity; index++)
    {
        if((*_map)->m_listArr[index] != NULL)
        {
            Destroy_List((*_map)->m_listArr[index], _keyDestroy, _valDestroy);
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
    Map_Result result;
    ListItr endOfList;
    Pair* pair;
    size_t hashIndx;
    void* val;
    
    result = CheckNull(_map, _key, _value);
    if(result != MAP_SUCCESS)   
    {
        return result;
    }
    result = HashMap_Find(_map, _key, &val);
    if(result != MAP_KEY_NOT_FOUND_ERROR)
    {
        return MAP_KEY_DUPLICATE_ERROR;
    }
    hashIndx = _map->m_hash(_key) % _map->m_capacity;
    if((_map->m_listArr[hashIndx] = ListCreate()) == NULL)
    {
        return MAP_ALLOCATION_ERROR;
    }
    pair = (Pair*)malloc(sizeof(Pair));
    if(NULL == pair)
    {
        return MAP_ALLOCATION_ERROR;
    }
    pair->m_key = (_key);
    pair->m_value = (_value);

    endOfList = ListItr_End(_map->m_listArr[hashIndx]);
    ListItr_InsertBefore(endOfList, pair);
    _map->m_nElements++;

    return MAP_SUCCESS;
}
/************************************************************************/
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, const void** _pKey, void** _pValue)
{
	size_t hashNum;
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
	hashNum = _map->m_hash(_searchKey) % _map->m_capacity;
	end = ListItr_End(_map->m_listArr[hashNum]);
	
	itr = isFound(_map, _searchKey, hashNum);
	if (ListItr_Equals(itr, end))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	pair = (Pair*)ListItr_Remove(itr);
	_map->m_nElements--;
	*_pValue = pair->m_value;
	*_pKey = pair->m_key;
	free(pair);
	return MAP_SUCCESS;
}
/************************************************************************/
Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
    ListItr endOfList, itr;
    size_t hashIndx; 
    if(NULL == _map)
    {
        return MAP_ALLOCATION_ERROR;
    }
    if(_key == NULL)
    {
        return MAP_KEY_NULL_ERROR;
    }
    hashIndx = _map->m_hash(_key) % _map->m_capacity;
    if(_map->m_listArr[hashIndx])
    {
        itr = isFound(_map, _key, hashIndx);
        endOfList = ListItr_End(_map->m_listArr[hashIndx]);
        if(itr != endOfList)
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
    if(NULL == _map)
    {
        return 0;
    }

    return _map->m_nElements;
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
/************************************************************************/
int IsEqualKeys(void *_hashKey, void *_keyToFind)
{
    FindKey* findKey = (FindKey*)_keyToFind;
	Pair* hashKey = (Pair*)_hashKey;
	return findKey->m_compare(hashKey->m_key, findKey->m_key);
}
/************************************************************************/
static ListItr isFound(const HashMap* _map, const void* _key, size_t _hashIndx)
{
    ListItr beginOfList, endOfList;
    FindKey context;
    if(NULL == _map->m_listArr[_hashIndx])
    {
        return NULL;
    }
    context.m_key = _key;
    context.m_compare = _map->m_isEqual;

    beginOfList = ListItr_Begin(_map->m_listArr[_hashIndx]);
    endOfList = ListItr_End(_map->m_listArr[_hashIndx]);
    ListItr_FindFirst(beginOfList, endOfList, IsEqualKeys, &context);
}
/************************************************************************/
/*size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{

}*/
/************************************************************************/
/*Map_Stats HashMap_GetStatistics(const HashMap* _map)
{

}*/
/************************************************************************/
/*Map_Result HashMap_Rehash(HashMap *_map, size_t newCapacity)
{

}*/
/************************************************************************/
