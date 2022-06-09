#include <stdio.h>

int arrayAverage(int _arr[], int _size)
{
	int i, sum;
	for(i = 0; i < _size; ++i)
	{
		sum += _arr[i];	
	}
	
	return sum;	
}
