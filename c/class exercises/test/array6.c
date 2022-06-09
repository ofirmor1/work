#include <stdio.h>
#include <stddef.h>
#define ARR_MIN_SIZE 1
#define ERROR -1
#define VALID -2

int isValidSize(int* arr, int arraySize)
{
	if (arraySize < ARR_MIN_SIZE)
	{
		return ERROR;
	}
	else
	{
		return VALID;
	}
}

int binarySearch(int* arr,int _size,int _numToSearch,int _left,int _right)
{
	int mid;
	if(_left < _right)
	{
		mid = _left + (_right - _left)/2;
		if(arr[mid] == _numToSearch)
		{
			return mid;
		}
		else if(arr[mid] < _numToSearch)
		{
			return binarySearch(arr, _size, _numToSearch, mid-1, _right);
		}	
		else if (arr[mid] > _numToSearch)
		{
			return binarySearch(arr, _size, _numToSearch,_left,mid-1);
		}
	}
	return ERROR;
}

int main(void)
{
	int result,isValid;
	int numToSearch;
	int arr[] = {1,3,5,6,8,9};
	size_t arraySize = sizeof(arr)/sizeof(arr[0]);
	numToSearch = 3;
	printf("%ld\n", arraySize);
	if(isValid = (isValidSize(arr,arraySize) != ERROR))
	{
		result = binarySearch(arr,arraySize,numToSearch, 0, arraySize);	
	}
	printf("%d\n", result);
	
}
