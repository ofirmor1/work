#include <stdio.h>


int printArray(int *ptr,int SizeOfArr)
{
	int i;
	for(i=0;i<SizeOfArr;i++)
	{
		printf("%d, ",ptr[i]);
	}
	printf("\n");
}

int SwapNumbers(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	
}


int FuncEvenAndOddSort(int *ptr,int SizeOfArr)
{
	int i;
	int j;
	for (j=0;j<SizeOfArr-1;j++)
	{		
		for(i=0;i<SizeOfArr-j-1;i++)
		{
			if(ptr[i]%2 && !(ptr[i+1]%2))
			{
				SwapNumbers(&ptr[i], &ptr[i+1]);
			}
		}
		

	}
}
