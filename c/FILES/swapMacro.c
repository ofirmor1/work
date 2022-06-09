#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(x, y) { int temp = x; x = y; y = temp; }

int SwapNumbers(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int BubbleSort(int _array[], int _size)
{
	int i,j, flag = 0;
	for (i = 0; i < _size-1; i++)
	{
		flag = 0;
		for(j = 0; j < _size-1-i; j++)
		{
			if(_array[j] > _array[j+1])
			{
				flag = 1;
				SwapNumbers(&_array[j],&_array[j+1]);
			}
		}
		if(!flag)
		{
			return;
		}
	}
}

int BubbleSortMacro(int _array[], int _size)
{
	int i,j, flag = 0;
	for (i = 0; i < _size-1; i++)
	{
		flag = 0;
		for(j = 0; j < _size-1-i; j++)
		{
			if(_array[j] > _array[j+1])
			{
				flag = 1;
				swap(_array[j],_array[j+1]);
			}
		}
		if(!flag)
		{
			return;
		}
	}
}

int main()
{
   int i;
   double result;
   int array[50000] = {0};
   int size = sizeof(array)/sizeof(array[0]);
   time_t t, clock_t, start_t, end_t, total_t;
   srand((unsigned) time(&t));
   for(i = 0; i < size; i++)
   {
   	array[i] = rand() % 50000;
   }

   start_t = clock();
   BubbleSort(array, size);
   end_t = clock();
   printf("Before swap Function call, start_t = %ld\n", start_t);
   printf("End of array loop, end_t = %ld\n", end_t);
   result = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %f\n", result  );
   for(i = 0; i < size; i++)
   {
   	array[i] = rand() % 50000;
   }


  start_t = clock();
   BubbleSortMacro(array, size);
   end_t = clock();
   printf("Before swap MACRO call, start_t = %ld\n", start_t);
   printf("End of array loop, end_t = %ld\n", end_t);
   result = (double)(end_t - start_t) /CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %f\n", result);
}
