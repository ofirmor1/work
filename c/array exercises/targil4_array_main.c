#include <stdio.h>

/*
the output shuld be: {0,2,4,8,1,3,5,7,9,13}
*/
int main()
{
	int size,i;
	int arr[10] = {1,3,0,2,5,8,4,13,7,9};
	size = sizeof(arr)/sizeof(arr[0]);
	printf("The original array is: \n");
	printArrayValues(arr,size);
	sortArray(arr, size);
	swapAllValues(int _arr[], int _size);
	sortArrayEvenOdd(int _arr[], int _size);
	printf("the sorted array is: \n");
	printArrayValues(arr,size);
	printf("\n");
	
}
