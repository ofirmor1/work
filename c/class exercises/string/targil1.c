#include <stdio.h>
#include <string.h>
#include "targil1.h"

char* reverseString(char *str)
{
	int indexLast,indexFirst,strLength,temp;
	char newStr, lastChar;
	strLength = strlen(str);
	lastChar = strLength-1;
	for(indexFirst = 0, indexLast = strLength-1; indexFirst < indexLast; indexFirst++,indexLast--)
	{
		temp = str[indexFirst];
		str[indexFirst] = str[indexLast];
		str[indexLast] = temp;
	}
	
	return str;
}
