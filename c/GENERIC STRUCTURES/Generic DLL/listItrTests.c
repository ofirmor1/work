#include <stdio.h>
#include "genericDll.h"
#include "listItr.h"

int main(void)
{
	int x, y, result;
	ListItr itr, itrBegin;
	List* list = ListCreate();
	/******************************LIST ITTERATE TESTS*******************************/
	printf("/*********************BEGIN TESTS*************************/");
	x = 2;
	y = 4;	

	ListPushHead(list,&x);
	itr = ListItrBegin(list);
	if(*(int*)ListItrGet(itr) == 2)
	{
		printf("\nListPushHead test - pass");
		printf("\nListItrBegin test - pass");
		printf("\nListItrGet test - pass");
	}
	printf("\n");
	ListPushHead(list,&y);
	itr = ListItrNext(list);
	if(*(int*)ListItrGet(itr) == 4)
	{
		printf("ListItrNext test - pass");
	}
	printf("\n ");
	itrBegin = ListItrBegin(list);
	if(!ListItrEquals(itr, itrBegin))
	{	
		printf("ListItrEquals test  - pass");
	}
	/*ListDestroy(&list,NULL);*/
}
