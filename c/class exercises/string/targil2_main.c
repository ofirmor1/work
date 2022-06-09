#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "abba";
	if (isPalindrome(str) == 1)
	{
		printf("Is palindrome");
	}
	else if(isPalindrome(str) == 0)
	{
		printf("Is NOT palindrome");
	}
	
	return 0;
}
