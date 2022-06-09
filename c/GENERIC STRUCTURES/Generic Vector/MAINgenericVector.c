#include <stddef.h>  /* size_t */
#include "genericVector.h"
#include <stdio.h>
#define SIZE 5

typedef struct Person 
{
	int m_id;
	char m_name[128];
	int m_age;
}Person;
/***********************************************************/
int PrintInt(void* _element, size_t _index, void* _context)
{
	/*printf("%d,",*((int*)_element));*/
	return 1;
}
/***********************************************************/
int PrintPerson(void* _element, size_t _index, void* _context)
{
	Person* temp;

	temp = (Person*)_element;
	printf("ID:%d\nName:%s\nAge:%d\n\n\n",temp->m_id,temp->m_name,temp->m_age);
}
/***********************************************************/
size_t VectorForEach( _vector, maxElement , index)
{

}
/***********************************************************/
int FindMaxInt(const void * _element, size_t _index, void* _context)
{
	if(_index == 0)
	{
		*((int*)_context) = *((int*)_element)
	}
	if(*((int*)_context) < *((int*)_element)
	{
		*((int*)_context) = *((int*)_element)
	}

	return 1;
}
/***********************************************************/
int main (void)
{
	Person nodeArray[SIZE] = {{1,"blabla",40},{2,"blabla",50},{3,"blabla",45},
							 {4,"blabla",20},{5,"blabla",80}};
	int array[SIZE] = {5,4,3,2,1};
	Vector* vecPtr;
	VectorResult check;
	int index, itemAdd;
	int* itemRemove;
	int max;
	

	vecPtr = VectorCreate(1,1);
	
	for(index=0; index<SIZE; index++)
	{
		itemAdd = array[index];
		check =VectorAppend(vecPtr, &itemAdd);
	}

	VectorForEach(vecPtr, PrintInt, NULL);

	for(index=0; index<SIZE; index++)
	{
		check =VectorRemove(vecPtr, (void*)&itemRemove);
		printf("itemRemove %d\n",*itemRemove);
	}
	VectorForEach(vecPtr, PrintInt, NULL);

}
