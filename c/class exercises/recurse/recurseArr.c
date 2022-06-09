#include <stdio.h>

int RecurseArr(int _arr[], int _size)
{
	if(_size == 0)
	{
		return 0;
	}
	return RecurseArr(_arr, _size-1)+_arr[_size-1];
}

int main(void)
{
	int sum;
	int arr []= {1,3,5};
	sum = RecurseArr(arr, 3);
	printf("%d \n", sum);
	
}
