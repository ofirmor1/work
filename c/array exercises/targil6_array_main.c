#include <stdio.h>
#define ARR_MIN_SIZE 1
#define ERROR -1
#define VALID 0

/*
...
.
...
*/
int main()
{
	int result,isValid,size, num = 13;
	int arr[10] = {0,2,4,6,7,9,11,13,14,21};
	size = sizeof(arr)/sizeof(arr[0]);
	printf("%d \n", size);
	printf("The array elements are: \n");
	printArrayValues(arr,size);
	if (isValid = ArraySizeCheck(arr, size) != ERROR)
	{
		 result = binarySearch(arr, size, num, size, 0) +1;
	}
	else
	{
		printf("Error - array is not defined well");
	}
	printf("The number %d appears in the %d'th place in array.\n ", num, result);
	
}
