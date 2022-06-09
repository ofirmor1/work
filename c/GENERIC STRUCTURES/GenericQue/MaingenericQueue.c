#include <stdlib.h>	
#include "genericQueue.h"
#include<stdio.h>
#define SIZE 5

typedef struct Person 
{
	int m_id;
	char m_name[128];
	int m_age;
}Person;
/************************************************************************************/
int PrintInt(const void* _element, void* _context)
{
	printf("%d,",*((int*)_element));
	return 1;
}

int printPerson(const void* _element, void* _context)
{
	Person* temp;

	temp = (Person*)_element;
	printf("ID:%d\nName:%s\nAge:%d\n\n\n",temp->m_id,temp->m_name,temp->m_age);
}

void DestroyInt(void* _element)
{
	
}
/************************************************************************************/
int main (void)
{
	Person PersonArray[SIZE] = {{1,"blabla",40},{2,"blabla",50},{3,"blabla",45},
							 {4,"blabla",20},{5,"blabla",80}};
	int array[SIZE] = {5,4,3,2,1};

	Queue* quePtr;
	QueueResult check;
	int index, itemAdd;
	int* itemRemove;
	Person* personItemRemove;
	int max;

	quePtr = QueueCreate(SIZE);
	for(index=0; index<SIZE; index++)
	{
		check = QueueInsert(quePtr,&array[index]);
	}
	QueueForEach(quePtr,PrintInt, NULL);
	
	printf("\n");
	check = QueueRemove(quePtr,(void*)&itemRemove);
	QueueForEach(quePtr,PrintInt, NULL);

	printf("\n");
	printf("QueueIsEmpty :%ld\n",QueueIsEmpty(quePtr));

	check = QueueRemove(quePtr,(void*)&itemRemove);
	check = QueueRemove(quePtr,(void*)&itemRemove);
	check = QueueRemove(quePtr,(void*)&itemRemove);
	check = QueueRemove(quePtr,(void*)&itemRemove);
	printf("QueueIsEmpty :%ld\n",QueueIsEmpty(quePtr));

	QueueDestroy(&quePtr, DestroyInt);

/*	quePtr = QueueCreate(SIZE);
		for(index=0; index<SIZE; index++)
	{
		check = QueueInsert(quePtr,&PersonArray[index]);
	}
	QueueForEach(quePtr,printPerson, NULL);
	printf("*************************************************************");
	printf("\n");
	check = QueueRemove(quePtr,(void*)&personItemRemove);
	QueueForEach(quePtr,printPerson, NULL);

	printf("\n");
	printf("QueueIsEmpty :%ld\n",QueueIsEmpty(quePtr));

	check = QueueRemove(quePtr,(void*)&personItemRemove);
	check = QueueRemove(quePtr,(void*)&personItemRemove);
	check = QueueRemove(quePtr,(void*)&personItemRemove);
	check = QueueRemove(quePtr,(void*)&personItemRemove);
	printf("QueueIsEmpty :%ld\n",QueueIsEmpty(quePtr));
*/	
	
	
}

