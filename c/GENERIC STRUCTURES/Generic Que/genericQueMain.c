#include <stdlib.h> 
#include "genericQue.h"
#include <stdio.h>

#define SIZE 5

typedef struct Person 
{
	int m_id;
	char m_name[128];
	int m_age;
}Person;

int PrintInt(const void* _element, void* _context)
{
	printf("%d,",*((int*)_element));
	return 1;
}

int main (void)
{
	Person nodeArray[SIZE] = {{1,"blabla",40},{2,"blabla",50},{3,"blabla",45},
							 {4,"blabla",20},{5,"blabla",80}};
	int array[SIZE] = {5,4,3,2,1};
	Queue* queue;
	QueueResult check;
	int index;
	int* itemRemove;
	int max;
	
	queue = QueueCreate(5);
	
	for(index = 0; index < SIZE; index++)
	{
		check = QueueInsert(queue, &array[index]);
	}

	QueueForEach(queue, PrintInt, 0);

	for(index = 0; index < SIZE; index++)
	{
		check = QueueRemove(queue, (void*)&itemRemove);
		printf("itemRemove %d\n",*itemRemove);
	}
	QueueForEach(queue, PrintInt, NULL);
}
