#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_ERROR -1
#define SUCCESS 1

int checkParams(char *str)
{
	if(str == NULL)
	{
		return NULL_ERROR;
	}
}
char* reverse(char *str)
{
	int i,j,temp, isError;
	int last = strlen(str);
	isError = checkParams(str);
	for(i = 0, j = last-1; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}
	
	
int main(void)
{
	int isError;
	char str[] = "";
	printf(" %c\n ", *str);
	printf("The original world is: %s\n ", str) ;
	isError = checkParams(str);
	if (isError != -1)
	{
		puts(reverse(str));
		printf("The original world is: %s\n ", str) ;
	}
	else 
	{
		printf("The string is empty: %d\n ", isError);
	}

	
	return 0;
	
}
