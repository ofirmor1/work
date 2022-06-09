#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(x, y) { int temp = x; x = y; y = temp; }

int SwapNumbers(int num1, int num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
void arraySwapByFunction(int *_array, int size)
{
	int i;
   clock_t start_t, end_t, total_t;
	printf("Before swap Function call, start_t = %ld\n", start_t);
   for(i = 0; i < size; i++)
   {
   		SwapNumbers(_array[i],_array[i+1]);
   }
end_t = clock();
   printf("End of array loop, end_t = %ld\n", end_t);
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU: %ld\n", total_t  );
}

void arraySwapByMacro(int *_array, int size)
{
	int i;
   clock_t start_t, end_t, total_t;
	printf("Before swap MACRO call, start_t = %ld\n", start_t);
   for(i = 0; i < size; i++)
   {
   		swap(_array[i],_array[i+1]);
   }
   end_t = clock();
   printf("End of array loop, end_t = %ld\n", end_t);
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time taken by CPU: %ld\n", total_t );
}
int main()
{
   int i;
   int array[50000] = {0};
   int size = sizeof(array)/sizeof(array[0]);
   time_t t;
   srand((unsigned) time(&t));
   for(i = 0; i < size; i++)
   {
   	array[i] = rand() % 50;
   }
   arraySwapByMacro(array, size);
   arraySwapByMacro(array, size);
  
   
  
}
