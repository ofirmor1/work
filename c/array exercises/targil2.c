#include <stdio.h>
#define MIN_NUMBER 2


/*
This program take a number as an input and return is Factorial.
*/

int factorial(int num)
{
	
	int i,factorial = num;
	for (i = num; num > 0; i--)
	{
		factorial *=(num-1);
		num--;	
	}	
}
int main(void)
{
	int i, number;
	printf("Please enter a number :\n");
	scanf("%d", &number);
	printf("The factorial of %d is: %d\n", number, factorial(number));
}
