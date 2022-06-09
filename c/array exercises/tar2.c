#include <stdio.h>

int isAscending(int num)
{
	int firstFromLast;
	int secondFromLast;
	while(num > 0)
	{
		firstFromLast = num % 10;
		secondFromLast = firstFromLast % 10;
		if(firstFromLast >= secondFromLast)
		{
			num /= num;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	int num = 1234;
	int result = isAscending(&num);
	printf("%d\n", result);
	return 0;
}	
