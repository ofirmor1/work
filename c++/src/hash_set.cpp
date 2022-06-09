#include <stdio.h>
#include <stdlib.h>
#include "hash_set.hpp"
#define PERCENT(x)	((x) * 1.3)
#define FOUND 1
#define  NOT_FOUND 0

struct Hash
{
void** m_data;
char* m_state;/*0->empty,wasn't occupied, 
                1->empty,was occupied,
                2 - occupied*/
size_t (*m_hashFunction)(void* _data);
int (*m_equalityFunction)(void* _firstData, void* _secondData);
size_t m_hashSize; /*original size given by the client*/
size_t m_capacity; /*real hash size */
size_t m_numOfItems; /*number of occupied places in the table*/
size_t m_maxOfRehashOperations; /*maximum amount of rehash operations
which have been done over one insertion*/
size_t m_counterOfInsertions; /*total amount of insertions into the table*/
size_t m_allRehashOperations; /*all rehash operations mutual counter*/
};

static HashSet_Result IsHashSetEmpty(Hash* _hash);
/************************************************************************/
Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int
(*_equalityFunction)(void*, void*))
{
    Hash* hashSet;
    if(_size < 1)
    {
        return NULL;
    }
    hashSet = (Hash*)malloc(sizeof(Hash));
    if(NULL == hashSet)
    {
        return NULL;
    }
    hashSet->m_hashSize = _size;
    hashSet->m_capacity  = PERCENT(_size);
    hashSet->m_state = calloc(hashSet->m_capacity ,sizeof(Hash));
    hashSet->m_numOfItems = 0;
    hashSet->m_maxOfRehashOperations = 0;
    hashSet->m_counterOfInsertions = 0;
    hashSet->m_allRehashOperations = 0;

    hashSet->m_data = (Hash**)calloc(hashSet->m_capacity, sizeof(Hash*));
    if(NULL == hashSet->m_data)
    {
        free(hashSet);
        return NULL;
    }

    return hashSet;

}
/************************************************************************/
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
    int index;
    if(NULL == _hash || NULL == *_hash)
    {
        return;
    }
    for(index = 0; index < (*_hash)->m_capacity; index++)
    {
        if((*_hash)->m_data[index] != NULL)
        {
            _keyDestroy((*_hash)->m_data[index]);
            _keyDestroy((*_hash)->m_state[index]);
        }
    }
    free((*_hash)->m_data);
    free(*_hash);
    *_hash = NULL;
}
/************************************************************************/
HashSet_Result HashInsert(Hash* _hash, void* _data)
{
    HashSet_Result result;
    size_t hashNum;
    void* val;
    if(_hash == NULL)
    {
        return SET_UNINITIALIZED;
    }
    if(_data == NULL)
    {
        return SET_KEY_NOT_FOUND;
    }
    result = HashSet_Find(_hash, _data);
    if(result != SET_KEY_NOT_FOUND)
    {
        return SET_KEY_DUPLICATE;
    }
    hashNum = _hash->m_hashFunction(_data) % _hash->m_capacity;
    if(NULL == _hash->m_data[hashNum])
    {
        _hash->m_data[hashNum] = _data;
    }
    _hash->m_numOfItems++;
    _hash->m_state[hashNum] = 2;
    return SET_SUCCESS;

}
/************************************************************************/
HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
    size_t hashNum;
	if(_hash == NULL)
	{
		return SET_UNINITIALIZED;
	}
    if(_key == NULL)
	{
		return SET_KEY_NULL_ERROR;
	}
    hashNum = _hash->m_hashFunction(_key) % _hash->m_capacity;
    if(_hash->m_data[hashNum] == _key)
    {
        _hash->m_state[hashNum] += 1;
        *_data = _hash->m_data[hashNum];
    }
    else if(NULL == _hash->m_data[hashNum])
    {
        if(_hash->m_state[hashNum] == 1)
        {
            SET_KEY_NOT_FOUND;
        }
        else
        {
            hashNum++;
            _hash->m_maxOfRehashOperations++;
        }
        
    }
    _hash->m_numOfItems--;
    *_data =_hash->m_data;

    return SET_SUCCESS;
}
/************************************************************************/
int HashIsFound(const Hash* _hash, void* _key)
{
    if(NULL == _hash)
    {
        return 0;
    }
    hashNum = _hash->m_hashFunction(_key) % _hash->m_capacity;
    if((_hash->m_data[hashNum] == _key) && _hash->m_state[hashNum] == 2)
    {
        return FOUND;
    }
    if((_hash->m_data[hashNum] == _key) && _hash->m_state[hashNum] == 1)
    {
        return FOUND;
    }

}
/************************************************************************/
size_t HashNumOfItems(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }

    return _hash->m_numOfItems;
}
/************************************************************************/
size_t HashCapacity(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }
    
    return _hash->m_capacity;
}
/************************************************************************/
void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
    size_t counter = 0;
    size_t index = 0;

    while(counter < _hash->m_numOfItems)
    {
        if(_hash->m_state[index] == 2)
        {
            PrintKey(_hash->m_state[index]);
            counter++;
        }
        index++;
    }
}
/************************************************************************/

static HashSet_Result IsHashSetEmpty(Hash* _hash)
{
    if(_hash->m_numOfItems == 0)
    {
    	return SET_IS_EMPTY;
    }
    
    return SET_IS_NOT_EMPY;
}
/************************************************************************/
/*double HashAverageRehashes(const Hash* _hash)
{

}
/************************************************************************/
/*size_t HashMaxReHash(const Hash* _hash)
{

}
*/
/************************************************************************/
bool IntSet::contains(int e)
{
    return HashIsFound(hs, &e) ? true:false;
}
