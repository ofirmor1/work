#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int palindrome = 1;
	int newNum,num,ezer = 1,count,hishuv;
	printf("Please enter a number: ");
	scanf("%d" , &num);
	while(ezer > 0)
	{	
		count = 0;
		newNum = num/10;
		printf("%d\n", newNum);
		while(newNum > 10)
		{
			newNum = newNum / 10;
			count++;
			printf("%d %d\n", newNum,num);
		}
		if (newNum != (num%10))
		{
			printf("The number you've entered is not Palindrome\n");
			palindrome = 0;
			ezer = -1;
		}
		else
		{
			printf("%d\n", count);
			num = num/10;
			printf("%d\n", num);
			num -= newNum*pow(10, count);
			printf("%d\n", num);
		}
	}
	
	if (palindrome == 1)
	{
		printf("The number you've entered is Palindrome\n");
	}
	
	return 0;
}
