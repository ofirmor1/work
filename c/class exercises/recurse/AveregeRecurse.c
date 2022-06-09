#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Average(int *_arr, int _size)
{	
	if(_size == 1)
	{
		return _arr[0];
	}
	return (_arr[_size-1]+_size*Average(_arr,_size-1))/_size;
}

int main(void)
{
	int arr[] = {1,3,5,7};
	int average, i = 0;
	int len = sizeof(arr)/sizeof(arr[0]);
	while(i < len)
	{
	printf("%d ",arr[i]);
	i++;
	}
	average = Average(arr, len);
	printf("The Average of the array is: %d\n", average);
}
