#include <stdio.h>
#define ARR_MIN_SIZE 1
#define ERROR -1
#define VALID 0

int ArraySizeCheck(int _arr[], int _size)
{
	if(_size < ARR_MIN_SIZE)
	{
		return ERROR;
	}
	else if(_size == ARR_MIN_SIZE)
	{
		return _arr[0];
	}
	else
	{
		return VALID;
	}
}

int binarySearch(int _arr[], int _size, int _num,int _right,int _left)
{
	int mid;
	if(_right >= _left)
	{
		mid = _left + (_right - _left)/2;
		if(_arr[mid] == _num)
		{
			return mid;
		}
		else if(_arr[mid] > _num)
		{
			return binarySearch(_arr, _size, _num, mid-1, _left);
		}
		else if(_arr[mid] > _num)
		{
			return binarySearch(_arr, _size, _num, _right, mid-1);
		}
	}
	
	return -1;
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
