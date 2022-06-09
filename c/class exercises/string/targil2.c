#include <stdio.h>
#include <string.h>
#include "targil2.h"	

int isPalindrome(char* _str)
{'	int strLen = strlen(_str);;
	char *leftPtr = NULL, *rightPtr = NULL;
	if(strLen < 1)
	{
		return ERROR;
	}
		if(strLen == 1)
	{
		return 0;
	}
	int indexLast,indexFirst,strLength,temp;
	for(indexFirst = 0, indexLast = strLength-1; indexFirst < indexLast; indexFirst++,indexLast--)
	{	
		if(str[indexFirst] != str[indexLast])
		{
			return 0;
		}
	}
	return 1;
}
