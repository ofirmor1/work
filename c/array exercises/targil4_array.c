#include <stdio.h>
#define ARR_MIN_SIZE 1
#define ERROR -1

int sortArray(int _arr[], int _size)
{
	int i,j,temp;/*swapCounter = 1;*/
	if(_size < ARR_MIN_SIZE)
	{
		return ERROR;
	}
	else if (_size == ARR_MIN_SIZE)
	{
		return _arr[0];
	}
	while(_size > 1/* && swapCounter != 0*/)
	{
		swapValues(int _arr[], int _size);/*swapCounter = 0;*/
		_size--;	
	}
} 	
int swapAllValues(int *arr, int _size)
{
	int i,j,temp;
	for(i = 0,j = 1; (i < _size-1) && (j < _size); i++, j++)
		{	
			if(_arr[j] < i+1)
			{
				swapTwoValues(_arr + i, arr + j);
				/*swapCounter++;*/
			}
		}
}

int swapTwoValues(int *first, int *second)
{
	int temp;
	temp = *first;
	*second = *first;
	*first = *second;
}

int sortArrayEvenOdd(int _arr[], int _size)
{	int i, temp,last_even;
	int index_left = 0;
	int index_right = _size-1;
	for(index_left = 0; index_left < index_right; index_left++)
	{
		if(_arr[index_left] % 2 == 0) 
		{
			if(_arr[index_right] % 2 == 0)
			{
				swapTwoValues(int _arr[], index_left+1, index_right);
			}
		}
		else
		{
			if(_arr[index_right] % 2 != 0)
			{
				swapTwoValues(int _arr[],int _size, int index_left+1,int index_right);					
			}
		}
		index_right--;
	}
	return 0;
}
	
int printArrayValues(int _arr[], int _size)
{
	int i;
	for(i = 0; i < _size; i++)
	{
		printf("%d ", _arr[i]);
	}
	putchar('\n');
	return 0;
}
