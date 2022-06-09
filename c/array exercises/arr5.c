#include <stdio.h>
#define ARR_MIN_SIZE 1

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
		for(i = 0; i < _size-1; i++)
		{
			if(_arr[i] == 1)
			{
				for(j = i+1; j < _size; j++)
				{
					if(_arr[j] == 0)
					{
						ezer = _arr[i];
						_arr[i] = _arr[j];
						_arr[j] = ezer;
						break; 
					}
				}
			}
		}
	}
	return 0;
}
