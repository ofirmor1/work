#include <stdio.h>

int main()
{
	int i,size;
	int arr[] = {1,0,0,1,1,1,0,1,0,1};
	size = sizeof(arr)/sizeof(arr[0]);
	sortArray(arr, size);
	printf("the sorted array is: \n");
	for(i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
