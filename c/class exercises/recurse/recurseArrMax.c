#include <stdio.h>
#include <stdlib.h>

int MaxElement(int _arr[], int _size)
{
	int temp;
	if(_size) == 1
	{
		return _arr[0];
	}
	
	temp = MaxElement(arr,size-1);
	if(temp > _arr[0])
		{
			return temp;
		}
	else
	{
		return _arr[0];
	}
}

int main(void)
{
	int max;
	int arr[]= {1,3,5};
	max = MaxElement(arr, 3);
	printf("%d \n", sum);	
}
