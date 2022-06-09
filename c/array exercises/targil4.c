#include <stdio.h>
#define MIN_NUM 0

int ascendingOrder(int num)
{
	int originalNum = num, newNum = num/10;
	while(num >= MIN_NUM)
	{
		if (num < 10)
		{
			printf("The number %d is ascending order\n", originalNum);
			return 0;
			
		}
		else if ((num%10 - newNum%10) >= 0)
		{
			num /= 10;
			newNum = (num/10);
		}
		else
		{
			break;
		}
	}
	printf("The number %d is NOT ascending order\n", originalNum);
	return 0;
	
}
