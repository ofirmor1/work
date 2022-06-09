#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*****************Recurse Solution***********************/
/*
if(strLen < 1)
	{
		return ERROR;
	}
		if(strLen == 1)
	{
		return 0;
	}
*/
int ReverseStr(char *_str,int _indexFromFirst, int _indexFromLast)
{	
	char temp;
	temp = _str[_indexFromFirst];
	_str[_indexFromFirst] = _str[_indexFromLast];
	_str[_indexFromLast] = temp;
	if(_indexFromLast - _indexFromFirst) <= 1)
	{
		return;
	}
	return ReverseStr(_str,_indexFromFirst+1,_indexFromLast-1);
}

int main(void)
{
	int first = 0, last;
	char str[] = "Hello";
	last = strlen(str)-1;
	printf("The original string is: %s\n", str);
	ReverseStr(str,first,last);
	printf("The reverse string is: %s\n", str);
}
