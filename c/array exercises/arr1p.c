#include <stdio.h>

float arrayAverage(int arr[], int _size)
{
	int i;
	float sum, average;
	int *ptr = arr;
	for(i = 0; i < _size; ++i)
	{
		sum += *(ptr+1);
	}
	average = sum/_size;
	return average;	
}
