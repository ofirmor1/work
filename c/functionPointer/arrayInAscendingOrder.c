#include <stdio.h>
#include <time.h>
#define SIZE 50000
#define MAX_SIZE 5

int IsBigger(int num1, int num2)
{
	if(num1>num2)
	{
		return 1;
	}
	return 0;	
}

int IsSmaller(int num1, int num2)
{
	if(num1<num2)
	{
		return 1;
	}
	return 0;	
}

int IsEvenBeforeOdd(int num1, int num2)
{
	if(!(num1%2) && (num2%2))
	{
		return 1;
	}
	return 0;	
}

int IsEvenAfterOdd(int num1, int num2)
{
	if((num1%2) && !(num2%2))
	{
		return 1;
	}
	return 0;	
}

int main (void)
{
	int array[MAX_SIZE]= {3,1,18,4,5};

	printf("Is bigger\n");
	FuncarrayInAscendingOrder(IsBigger,array,MAX_SIZE);
	printArray(array,MAX_SIZE);
	printf("\n");

	printf("\nIs Smaller\n");
	FuncarrayInAscendingOrder(IsSmaller,array,MAX_SIZE);
	printArray(array,MAX_SIZE);
	printf("\n");

	printf("\nIs Even Before Odd\n");
	FuncarrayInAscendingOrder(IsEvenBeforeOdd,array,MAX_SIZE);
	printArray(array,MAX_SIZE);
	printf("\n");
	
	printf("\nIs Even After Odd\n");
	FuncarrayInAscendingOrder(IsEvenAfterOdd,array,MAX_SIZE);
	printArray(array,MAX_SIZE);
	printf("\n");
	
	

}




