#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ADTDefs.h"
#include "Vector.h"
#include "stack.h"


/***********************create**************************/
void CheckCreateSize0BlockSize0()
{
	if(StackCreate (0, 0)==NULL)
	{
		printf("CheckCreateSize0BlockSize0-pass\n");
	}
	else
	{
		printf("CheckCreateSize0BlockSize0-fail\n");
	}
}
/***********************create**************************/
void CheckCreateNull()
{
	if(StackCreate (3, 4)!=NULL)
	{
		printf("CheckCreateSize0BlockSize0-pass\n");
	}
	else
	{
		printf("CheckCreateSize0BlockSize0-fail\n");
	}

}
/***********************create**************************/
/*CheckCreateSize1BlockSize0*/
void CheckCreateSize1BlockSize0()
{
	if(StackCreate (1, 0)!=NULL)
	{
		printf("CheckCreateSize1BlockSize0-pass\n");
	}
	else
	{
		printf("CheckCreateSize1BlockSize0-fail\n");
	}

}

/***********************create**************************/
/*CheckCreateSize0BlockSize1*/
void CheckCreateSize0BlockSize1()
{
	if(StackCreate (0, 1)!=NULL)
	{
		printf("CheckCreateSize0BlockSize1-pass\n");
	}
	else
	{
		printf("CheckCreateSize0BlockSize1-fail\n");
	}

}
/***********************create**************************/
/*CheckCreateSizeUnderZero*/
void CheckCreateSizeUnderZero()
{
	if(StackCreate (-1, 3)==NULL)
	{
		printf("CheckCreateSizeUnderZero-pass\n");
	}
	else
	{
		printf("CheckCreateSizeUnderZero-fail\n");
	}

}

/***********************Destroy**************************/
/*void StackDestroy(Stack* _stack);*/

void CheckDestroyNull()
{
	Stack *ptrStack;
	ptrStack = StackCreate (0, 0);
	StackDestroy(ptrStack);
	printf("CheckDestroyNull-pass\n");	
}
/***********************Destroy**************************/
void CheckDestroyWorking()
{
	Stack *ptrStack;
	ptrStack = StackCreate (2, 3);
	StackDestroy(ptrStack);
	printf("CheckDestroyWorking-pass\n");	
}	
/***********************Destroy**************************/
void CheckDDestroy()
{
	Stack *ptrStack;
	ptrStack = StackCreate (2, 3);
	StackDestroy(ptrStack);
	StackDestroy(ptrStack);	
	printf("CheckDDestroy-pass\n");	
}	
/*************************Push****************************/
/*ADTErr StackPush (Stack* _stack, int _item);*/
void CheckPushNull()
{
	Stack *ptrStack;
	ptrStack = StackCreate (0, 0);
	if(StackPush (ptrStack, 3)==ERR_NOT_INITIALIZED)
	{
		printf("CheckPushNull-pass\n");
	}
	else
	{
		printf("CheckPushNull-fail\n");
	}
}
/*************************Push****************************/
/*IsPushWorking-----ADTErr StackPush (Stack* _stack, int _item)*/
void IsPushWorking()
{
	size_t numberOfElements;	
	int item;	
	Stack *ptrStack;
	ptrStack = StackCreate (2, 3);
	StackPush (ptrStack, 3);
	numberOfElements=GetNumberOfElements(ptrStack);
	StackTop (ptrStack, &item);
	if(item==3 && numberOfElements==1)
	{
		printf("IsPushWorking-pass\n");
	}
	else
	{
		printf("IsPushWorking-fail\n");
	}
}	


/***********************pop*******************************/
/*CheckPopNull*/ADTErr StackPop (Stack* _stack, int* _item)
void CheckPopNull()
{
	Stack *ptrStack;
	ptrStack = StackCreate (0, 0);
	if(StackPop (ptrStack, 3)==ERR_NOT_INITIALIZED)
	{
		printf("CheckPopNull-pass\n");
	}
	else
	{
		printf("CheckPopNull-fail\n");
	}

}


/***********************pop*******************************/
/*ADTErr StackPop (Stack* _stack, int* _item)*/
void IsPopWorking()
{
	size_t numberOfElements;
	int itemPop;	
	Stack *ptrStack;
	ptrStack = StackCreate (2, 3);
	StackPush (ptrStack, 3);
	StackPop (ptrStack, &itemPop);	
	numberOfElements = GetNumberOfElements(ptrStack);
	if(itemPop==3 && numberOfElements==0)
	{
		printf("IsPopWorking-pass\n");
	}
	else
	{
		printf("IsPopWorking-fail\n");
}

/***********************Top*******************************/
/*CheckTopNull*/
/***********************Top*******************************/
/*IsWorkingCheckTop*/
/*******************StackIsEmpty******************************/
/*CheckStackIsEmptyNull*/
/*******************StackIsEmpty******************************/
/*CheckStackIsEmpty*/
/*******************StackIsEmpty******************************/
/*CheckStackIsNotEmpty*/


int main (void)
{
CheckCreateSize0BlockSize0();
CheckCreateNull();
CheckDestroyNull();
CheckDestroyWorking();
CheckDDestroy();
CheckPushNull();

}

