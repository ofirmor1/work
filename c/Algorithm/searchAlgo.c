#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_OF_ELEMENTS 50000

int BetterSearch(int* _arr, int _size, int _num)
{
	int index, temp;
	if(_arr[_size-1] == _num)
	{
		return 1;
	}
	temp = _arr[_size-1];
	_arr[_size-1] = _num;
	for(index = 0;; index++)
	{
		if(_arr[index] == _num)
		{
			_arr[_size-1] = temp;
			break;
		}
	}
	_arr[_size-1] = temp;
	if(index == _size-1)
	{
		return 0;
	}
}
int NormalSearch(int* _arr, int _size, int _num)
{
	int index;
	for(index = 0; index < _size; index++)
	{
		if (_arr[index] == _num)
		{
			return 1;
		}
	}
	return 0;
}

int main (void)
{
	int i, randNum;
	clock_t t1, t2;
	int array1[NUM_OF_ELEMENTS]= {0};
	int array2[NUM_OF_ELEMENTS]= {0};
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		array1[i] = rand() % 10;	
		array2[i] = array1[i];
	}

	t1=clock();
	for(i = 0; i < 10000; i++)
	{
	NormalSearch(array1, NUM_OF_ELEMENTS, 11);
	}
	t2=clock();
	printf("Normal Search : %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	
	t1=clock();
	for(i = 0; i < 10000; i++)
	{
	BetterSearch(array2, NUM_OF_ELEMENTS, 11);
	}
	t2=clock();
	printf("Better Search : %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	/*VectorPrint(vecPtr);*/
	
}
