#include <stdio.h>
#define ARR_MIN_SIZE 1
#define ERROR -1

int sortArray(int _arr[], int _size)
{
	int i,j,temp,swapCounter = 1;
	if(_size < ARR_MIN_SIZE)
	{
		return ERROR;
	}
	else if (_size == ARR_MIN_SIZE)
	{
		return _arr[0];
	}
	while(_size > 1 && swapCounter != 0)
	{
		swapCounter = 0;
		for(i = 0,j = 1; (i < _size-1) && (j < _size); i++, j++)
		{	
			if(_arr[j] < _arr[i])
			{
				temp = _arr[j];
				_arr[j] = _arr[i];
				_arr[i] = temp;
				swapCounter++;
			}
		}
		_size--;	
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
