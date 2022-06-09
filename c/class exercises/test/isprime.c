#include <stdio.h>

#define ERROR -1

int isPrime(int number)
{
	int divider;
	int isPrime = 0;
	/*check the number*/
	if(number < 1)
	{
		return ERROR;
	}
	
	/*check if number is equal to 2 or greater then 2 and odd*/
	
	else if((number == 2) || (number > 2 && number % 2 != 0))
	{
		isPrime = 1;
		/*check if number is prime*/
		for(divider = 3; divider < number/2; divider += 2)
		{
			if(number % divider == 0) 
			{
				isPrime = 0;
				break; /*no reason to keep checking*/
			}
		}
	}
	return isPrime;
}

int main(void)
{
	int result;
	int number = 13;
	result = isPrime(number);
	if(result == 0)
	{
		printf("The number %d is not a prime number.. \n", number);
	}
	else if(result == 1)
	{
		printf("The number %d is a prime number.. \n", number);
	}
	else
	{
		printf("Please enter a positive number, above 0. \n");
	}
	
}
