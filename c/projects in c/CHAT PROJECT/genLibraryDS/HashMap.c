#include "HashMap.h"
#include "GenericDouble.h"
#include "Iterator.h"
#define EXIST 1
#define NOT_EXIST 0
#include <stdio.h>

struct Element{

const void* key;
const void* value;

};


struct HashMap{

List** list_data;
HashFunction hashFunc;
EqualityFunction equalFunc;
size_t capacity;
size_t numOfItems;

};

int checkCreateList(HashMap* _hash, size_t idx);
Element* createElement(const void* _key, const void* _value);
size_t FIndBiggerPrime(size_t _capacity);

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc){
	HashMap* newHash;
	if(_capacity == 0 || _hashFunc == NULL || _keysEqualFunc == NULL){
		return NULL;
	}
	newHash = (HashMap*) malloc(sizeof(HashMap));
	if(newHash == NULL){
		return NULL;
	}
	newHash -> capacity = FIndBiggerPrime(_capacity);
	newHash -> hashFunc = _hashFunc;
	newHash -> equalFunc = _keysEqualFunc;
	newHash -> list_data = (List**) calloc (newHash -> capacity, sizeof(List*));
	if(newHash -> list_data == NULL){
		return NULL;
	}
	newHash -> numOfItems = 0;
	return newHash;
}

void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value)){
	int i;
	ListItr *begin, *end, *current;
	void *elem;
	List *list;
	const void *tmp;
	if(_map == NULL || *_map == NULL){
		return ;
	}
	
	for(i = 0; i < (*_map) -> capacity; i++){
		list = (*_map) -> list_data[i];
		if(list != NULL){
			begin = ListItrBegin(list);
			end = ListItrEnd(list);
			current = begin;
			while(current != end){
				elem = ListItrGet(current);
				if(_keyDestroy !=NULL){
					tmp = ((Element*)elem) -> key;
					_keyDestroy((void*) tmp);
				}
				if(_valDestroy !=NULL){
					tmp = ((Element*)elem) -> value;
					_keyDestroy((void*) tmp);
				}
				free(elem);
				current = ListItrNext(current);
			}
		ListDestroy(&list, NULL);
		}
	}
	free((*_map) -> list_data);
	free(*_map);
	*_map = NULL;
}

int listLoop(const HashMap* _map, List * _list, const void* _searchKey, void** _pValue, void** _pKey, int toRemoveFlag){ 
	ListItr *begin, *end, *current;
	void *elem;
	const void *tmp;
	begin = ListItrBegin(_list);
	end = ListItrEnd(_list);
	current = begin;
	while(current != end){
		elem = ListItrGet(current);
		tmp = ((Element*)elem) -> key;
		if((_map -> equalFunc(tmp, _searchKey)) == 1){
			*_pValue = (void*)(((Element*)elem) -> value);
			if(toRemoveFlag){
				*_pKey = (void*)(((Element*)elem) -> key);
				ListItrRemove(current);
			}
			return MAP_SUCCESS;
		}
		current = ListItrNext(current);
	}
	return MAP_KEY_NOT_FOUND_ERROR;
}

int internalHashFind(const HashMap* _map, const void* _key, void** _pValue){
	size_t idx =0;
	List *myList;
	
	idx = (_map -> hashFunc(_key))%_map -> capacity;
	myList = _map -> list_data[idx];
	if(myList == NULL){
		return MAP_KEY_NOT_FOUND_ERROR;	
	}
	return listLoop(_map, myList, _key, _pValue, NULL ,0); 
} 

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue){
	if(_map == NULL || _pValue== NULL){
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_key == NULL){
		return MAP_KEY_NULL_ERROR;
	}
	return internalHashFind(_map,_key, _pValue);
}
	
Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value){
	List *newList;
	Element *newElem;
	size_t idx;
	void *i;
	if(_map == NULL){
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_key == NULL){
		return MAP_KEY_NULL_ERROR;
	}
	if(internalHashFind(_map,_key, &i) == 0){
		return MAP_KEY_DUPLICATE_ERROR;
	}
	idx = _map -> hashFunc(_key)% _map -> capacity;
	if(_map -> list_data[idx] == NULL){ /*create list*/
		newList = ListCreate();
		if(newList == NULL){
			return MAP_ALLOCATION_ERROR;
		}
		_map -> list_data[idx] = newList;
	}
	if((newElem = createElement(_key, _value)) == NULL){ /*only insert the data*/
		return MAP_ALLOCATION_ERROR;
	}
	ListPushTail(newList, newElem);
	_map -> numOfItems++;
	return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue){
	size_t idx=0;
	List *myList;
	if(_map == NULL || _pKey == NULL || _pValue == NULL){
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_searchKey == NULL){
		return MAP_KEY_NULL_ERROR;
	}
	idx = _map -> hashFunc(_searchKey) % _map -> capacity;
	myList = _map -> list_data[idx];
	if(myList == NULL){
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	if(listLoop(_map, myList, _searchKey, _pValue, _pKey,1) == MAP_SUCCESS){
		_map -> numOfItems--;
		return MAP_SUCCESS;
	}
	return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMap_Size(const HashMap* _map){
	if(_map == NULL){
		return 0;
	}
	return _map -> numOfItems;
}

size_t HashMap_capacity(const HashMap* _map){
	if(_map == NULL){
		return 0;
	}
	return _map -> capacity;
}


Element* createElement(const void* _key, const void* _value){
	Element *newElement;
	newElement = (Element*) malloc(sizeof(Element));
	if(newElement == NULL){
		return NULL;
	}
	newElement -> key = _key;
	newElement -> value = _value;

	return newElement;
}


size_t FIndBiggerPrime(size_t _capacity){
	size_t i = 0, flag;
	while(1){
		flag = 1;
		for(i = 2;i*i <= _capacity ; i++){
			if(_capacity % i == 0){
				flag = 0;
				break;
			}
		}
		if(flag == 1){	
			break;	
		}
		else{
			_capacity = _capacity+1;
		}
	}
	return _capacity;
}


void ListPrintINternal(List* _list){
	void *elem;
	const void *tmp;
	ListItr *begin, *end, *current;
	begin = ListItrBegin(_list);
	end = ListItrEnd(_list);
	current = begin;
	while(current != end){
		elem = ListItrGet(current);
		tmp = ((Element*)elem) -> key;
		printf("%d, ", *(int*)tmp);
		current = ListItrNext(current);
	}		
}

void PrintTable(HashMap* _hash){
	List *mylist;
	int i;
	for(i = 0; i < _hash -> capacity; i++){
		mylist = _hash -> list_data[i];
		if(mylist !=NULL){
			ListPrintINternal(mylist);
			printf("\n\n\n");
		}
	}
}


int compareFirstKey(HashMap* _hash, void *_key){
	size_t idx;
	List *myList;
	ListItr begin;
	const void *tmp;
	void *elem;
	idx = _hash -> hashFunc(_key) % _hash -> capacity;
	myList = _hash -> list_data[idx];
	begin = ListItrBegin(myList);
	elem = ListItrGet(begin);
	tmp = ((Element*)elem) -> key;
	if(_hash -> equalFunc(tmp, _key) ==1){
		return 1;
	}
	return 0;
}

int compareToSecondtKey(HashMap* _hash, void *_key){
	size_t idx;
	List *myList;
	ListItr begin, next;
	void const *tmp;
	void *elem;
	idx = _hash -> hashFunc(_key) % _hash -> capacity;
	myList = _hash -> list_data[idx];
	begin = ListItrBegin(myList);
	next = ListItrNext(begin);
	elem = ListItrGet(next);
	tmp = ((Element*)elem) -> key;
	if(_hash -> equalFunc(tmp, _key) ==1){
		return 1;
	}
	return 0;
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context){
	List *mylist;
	int i;
	void *elem;
	const void *tmp1;
	void *tmp2;
	ListItr *begin, *end, *current;
	for(i = 0; i < _map -> capacity; i++){
		mylist = _map -> list_data[i];
		if(mylist !=NULL){
			begin = ListItrBegin(mylist);
			end = ListItrEnd(mylist);
			current = begin;
			while(current != end){
				elem = ListItrGet(current);
				tmp1 = ((Element*)elem) -> key;
				tmp2 = ((void*)((Element*)elem) -> value);
				if(_action(tmp1, tmp2, _context) !=1){
					break;
				} 
				current = ListItrNext(current);
			}
		}
	}
}

			
		
