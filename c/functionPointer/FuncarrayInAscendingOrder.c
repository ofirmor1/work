#include <stdio.h>
#include "FuncarrayInAscendingOrder.h"
#include <time.h>
#define SWAP(x,y)\
		{		\
		int temp;\
		temp =x;\
		x=y;\
		y=temp;\
		}
			

static int SwapNumbers(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	
} 

int printArray(int *ptr,int SizeOfArr)
{
	int i;
	for(i=0;i<SizeOfArr;i++)
	{
		printf("%d, ",ptr[i]);
	}
}


int FuncarrayInAscendingOrder(int(*SortCriteria)(int,int),int *ptr,int SizeOfArr)
{
	register i;
	int j;
	int flag=0;

	for (j=0;j<SizeOfArr-1;j++)
	{	
		flag=0;		
		for(i=0;i<SizeOfArr-j-1;i++)
		{
			if(SortCriteria(ptr[i],ptr[i+1]))  /****insert here****/
			{
				SwapNumbers(&ptr[i], &ptr[i+1]);
				flag=1;			
			}

		}
		if(!flag)
		{
			return;
		}
		

	}
}


