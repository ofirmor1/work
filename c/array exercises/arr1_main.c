#include <stdio.h>

int main()
{
	int i, arraySize;
	float average;
	int arr[10] = {1,3,5,7,9,11,13,15,17,19};
	int *ptr = arr;
	arraySize = sizeof(arr)/sizeof(arr[0]);
	average = arrayAverage(arr, arraySize);
	printf("The array organs: ");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", *(ptr+i));
	}
	printf("\nThe average of array is: %.2f \n", average);
}
