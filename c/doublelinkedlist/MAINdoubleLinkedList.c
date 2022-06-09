#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkedList.h"
#include "ADTDefs.h"


int main (void)
{
	int data;
	int i;
	int array[5]= {1,2,3,4,5};
	List *listPtr;
	listPtr = ListCreate();
	/*ListPrint(listPtr);*/
	ListPushHead(listPtr, array[1]); /*2*/
	ListPushHead(listPtr, array[2]); /*3*/
	
	ListPushTail(listPtr, array[3]);/*4*/
	ListPushTail(listPtr, array[4]);/*5*/
	/*ListPrint(listPtr);*/

	ListPopHead(listPtr, &data);

	/*printf("%d\n",data);*/
	ListPopTail(listPtr, &data);
	ListPrint(listPtr);
	printf("PopTail %d\n\n",data);
	/*ListPrint(listPtr);*/
	ListPrint(listPtr);

	printf("ListCountItems %ld\n",ListCountItems(listPtr));

/*
	void ListDestroy(List* _list);

	

	ADTErr ListPopTail(List* _list, int* _data);



	int ListIsEmpty(List* _list);

	
*/

}
