#include <stdio>

bool is_palindrome(int num)
{
	int i;
	for (int i = num ; i > 0; i++)
	{
		if((num / 10) != (num % 2))
		{
			printf("The number is not palindrome");
			break;
		}
	}	
}
int main(void)
{
	int num;
	for (int i = num ; i > 0; i++)
	{
		if((num / 10) != (num % 2))
		{
			printf("The number is not polindrome");
			break;
		}
	}	
}

