#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IS_PALINDROM 1
#define IS_NOT_PALINDROM 0
/*****************Recurse Solution***********************/

int IsPalindrom(char *_str,int _indexFromFirst, int _indexFromLast)
{

	if(_str[_indexFromFirst] == _str[_indexFromLast])
	{
		return IS_PALINDROM;
	}
	else
	{
		return IS_NOT_PALINDROM;
	}
	return IsPalindrom(_str,_indexFromFirst+1,_indexFromLast-1);
}

int main(void)
{
	int first = 0, last,isPal;
	char str[] = "abba";
	last = strlen(str)-1;
	isPal = IsPalindrom(str,first,last);
	if(isPal == 1)
	{
		printf("The string %s is Palindrom\n", str);
	}
	else
	{
		printf("The string %s is not Palindrom\n", str);
	}
}
