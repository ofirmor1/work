#include <stdio.h>

int main()
{
	int arr[10] = {1,3,3,4,6,5,3,4,17,19};
	int i, arraySize, result = 0;;
	arraySize = sizeof(arr)/sizeof(arr[0]);
	sortArray(arr, arraySize);
	result = valueOccurMost(arr, arraySize);
	printf("The array values: ");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\nThe number %d is the most frequency value in the array. \n", result);
	
}
