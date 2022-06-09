#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector.h"
#include "ADTDefs.h"


int QuickSort(Vector* _vector, int _n)
{
	if(NULL == _vector)
	{
		
	}
}



int main(void)
{
   Vector* vectorPtr;
   
   double result;
   int array1[50000] = {0};
   int array2[50000] = {0};
   int size = sizeof(array1)/sizeof(array1[0]);
   time_t t, clock_t, start_t, end_t, total_t;
   srand((unsigned) time(&t));
   for(i = 0; i < size; i++)
   {
   	array1[i] = rand() % 50000;
   	array2[i] = array1[i];
   }
	
   start_t = clock();
   BubbleSort(array1, size);
   end_t = clock();
   printf("Before swap Function call, start_t = %ld\n", start_t);
   printf("End of array loop, end_t = %ld\n", end_t);
   result = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %f\n", result  );
  
  start_t = clock();
   BubbleSortMacro(array2, size);
   end_t = clock();
   printf("Before swap MACRO call, start_t = %ld\n", start_t);
   printf("End of array loop, end_t = %ld\n", end_t);
   result = (double)(end_t - start_t) /CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %f\n", result);
  printf(" %f\n", result);
}
