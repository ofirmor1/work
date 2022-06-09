#include <stdio.h>
#include "hashMap.h"
#include "genericDll.h"
#include "list_functions.h"
#include "list_Itr.h"


size_t hash(const void* _key)
{
	return (size_t)(*(int*)_key);
}

int Equal(const void* _firstKey, const void* _secondKey)
{
	return *(int*)_firstKey == *(int*)_secondKey;
}

HashMap* FillMap(int arr[], int size)
{
	int index = 0;
	HashMap* map = HashMap_Create(10,hash,Equal);
	while (index < size)
	{
		HashMap_Insert(map, &arr[index], &arr[index+1]);
		index += 2;
	}
	return map;
}
/**************************HASHMAP CREATE TESTS**************************/
void HashMapCreateTests()
{
	HashMap* map;

	if(HashMap_Create(0,NULL,NULL) == NULL)
	{
		printf("%35.35s - %s\n","capacity = 0 check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","capacity = 0 check","Fail");
	}
/***********************************************************************/
	if(HashMap_Create(5,NULL,Equal) == NULL)
	{
		printf("%35.35s - %s\n","EqualityFunction check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","EqualityFunction check","Fail");
	}
/***********************************************************************/	
	if(HashMap_Create(1,hash,NULL) == NULL)
	{
		printf("%35.35s - %s\n","HashFunction check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HashFunction check","Fail");
	}
/***********************************************************************/
	if((map = HashMap_Create(10,hash,Equal)) != NULL)
	{
		printf("%35.35s - %s\n","HashMap create is working check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HashMap create is working check","Fail");
	}
/***********************************************************************/
	map = HashMap_Create(10,hash,Equal);
	HashMap_Destroy(&map,NULL,NULL);
	if(NULL == map)
	{
		printf("%35.35s - %s\n","HashMap destroy is working check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HashMap destroy is working check","Fail");
	}
}
/**************************HASHMAP DESTROY TESTS**************************/
void DestroyCheck()
{
	HashMap* map = NULL;
	map = HashMap_Create(10,hash,Equal);
	HashMap_Destroy(&map,NULL,NULL);
	if(!map)
	{
		printf("%35.35s - %s\n","HASHMAP DESTROY is working check","Pass");
	}
	else
	{
		printf("%35.35s - %s\n","HASHMAP DESTROY is not working check","Pass");
	}
}
/***********************************************************************/
void DoubleDestroyCheck()
{
	HashMap* map = NULL;
	map = HashMap_Create(10,hash,Equal);
	HashMap_Destroy(&map,NULL,NULL);
	HashMap_Destroy(&map,NULL,NULL);
	if(!map)
	{
		printf("%35.35s - %s\n","HASHMAP DoubleDestroyCheck check","Pass");
	}
	else
	{
		printf("%35.35s - %s\n","HASHMAP DoubleDestroyCheck is not working check","Pass");
	}
}
/**************************HASHMAP INSERT TESTS**************************/
void InsertCheck()
{
	HashMap* map = NULL;
	int arr[] = {56,3,113,15,45,1,77,0,56,6};
	map = FillMap(arr, 7);
	if((HashMap_Insert(map, &arr[6], &arr[7])) == MAP_KEY_DUPLICATE_ERROR)
	
	{
		printf("%35.35s - %s\n","HASHMAP Insert is working check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HASHMAP Insert is working check","Fail");
	}
	HashMap_Destroy(&map,NULL,NULL);
}
/**************************HASHMAP REMOVE TESTS**************************/
void RemoveCheck()
{
	HashMap* map;
	int* key, *value;
	int arr[] = {56,3,113,15,45,1,77,0,56,6};
	map = FillMap(arr, 7);
	if((HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value)) == MAP_UNINITIALIZED_ERROR)
	{
		printf("%35.35s - %s\n","MAP_UNINITIALIZED_ERROR check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","MAP_UNINITIALIZED_ERROR check","Fail");
	}
/***********************************************************************/
	map = FillMap(arr, 7);
	if((HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value)) == MAP_SUCCESS)
	{
		printf("%35.35s - %s\n","MAP_SUCCESS check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","MAP_SUCCESS check","Fail");
	}
	
/***********************************************************************/
	if((HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value)) == MAP_KEY_NOT_FOUND_ERROR)
	{
		printf("%35.35s - %s\n","MAP_KEY_NOT_FOUND_ERROR check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","MAP_KEY_NOT_FOUND_ERROR check","Fail");
	}

	HashMap_Destroy(&map,NULL,NULL);
}
/**************************HASHMAP HASHFIND TESTS**************************/
void HashFindCheck()
{
	int arr[] = {56,3,113,15,45,1,77,0,56,6};
	int* key, *value;
	HashMap* map = NULL;
	map = FillMap(arr, 7);
	if((HashMap_Find(map, &arr[2], (void**)&value)) == MAP_SUCCESS)
	{
		printf("%35.35s - %s\n","MAP_SUCCESS check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","MAP_SUCCESS check","Fail");
	}
/***********************************************************************/
	if((HashMap_Remove(map, &arr[2], (const void**)&key, (void**)&value)) == MAP_SUCCESS)
	{
		printf("%35.35s - %s\n","HashFind MAP_SUCCESS check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HashFind MAP_SUCCESS check","Fail");
	}
	if((HashMap_Find(map, &arr[2], (void**)&value)) == MAP_KEY_NOT_FOUND_ERROR)
	{
		printf("%35.35s - %s\n","HashFind MAP_KEY_NOT_FOUND_ERROR check","Pass");	
	}
	else
	{
		printf("%35.35s - %s\n","HashFind MAP_KEY_NOT_FOUND_ERROR check","Fail");
	}
	HashMap_Destroy(&map,NULL,NULL);
}


int main(void)
{
	printf("*********************HASHMAP CREATE TESTS************************\n");
	HashMapCreateTests();
	printf("*********************HASHMAP DESTROY TESTS***********************\n");
	DestroyCheck();
	DoubleDestroyCheck();
	printf("*********************HASHMAP INSERT TESTS************************\n");
	InsertCheck();
	printf("*********************HASHMAP REMOVE TESTS************************");
	RemoveCheck();
	printf("**********************HASHMAP FIND TESTS*************************\n");
	HashFindCheck();
}
