#include <stdio.h>
#define ARR_MIN_SIZE 1

/*int arr[10] = {1,3,3,4,6,5,3,4,17,19}
The array values: 1 3 3 3 4 4 5 6 17 19 

*/
int valueOccurMost(int _arr[], int _size)
{
	int i,j,counter = 0;
	int occurMost = _arr[0],max_counter = 0;
	for(i = 0; i < _size; ++i)
	{
		counter = 1;
		for(j = i+1; j <_size; j++)
		{ 	
			if (_arr[j] == _arr[i])
			{
				counter++;
			}
			else
			{
				break;
			}
				
		}
		if(counter >= max_counter)
		{
			max_counter = counter;
			occurMost = _arr[i];
			i = j;
		}
	}
	return occurMost;	
}

int swap(int *_arr, int _size)
{
	int i,j,ezer;
	for(i = 0; i < _size-1; i++)
	{
		for(j = i+1; j < _size; j++)
		{
			if(_arr[i] > _arr[j])
			{
				ezer = _arr[i];
				_arr[i] = _arr[j];
				_arr[j] = ezer; 
			}
		}
	}
}
int sortArray(int _arr[], int _size)
{
	int i,j,ezer;
	if(_size < ARR_MIN_SIZE)
	{
		printf("The array is empty");
	}
	else if (_size == ARR_MIN_SIZE)
	{
		return _arr[0];
	}
	else
	{
		swap(_arr, _size);
	}
	return 0;
}
