#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0

int compareStr(char *str1, char *str2)
{
	int index;
	for(index = 0; index < strlen(str2); index++)
	{
		if(str1[index] != str2[index])
		{
			return 0;
		}
	}	
	return 1;
}

int RemoveChar(char *str, int index)
{
	while(str[index] != '\0')
	{
		str[index] = str[index+1];
		index++;
	}
}

int main(void)
{
	char str1[20] = "ABCDEF";
	char str2[20] = "CD";
	char newStr;
	int compare;
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int sizeStr1 = strlen(str1);
	int sizeStr2 = strlen(str2);
	
	if( str1 == NULL || str2 == NULL)
	{
		return ERROR;
	}
	for(index1 = 0; index1 < sizeStr1; index2++)
	{
		for(index2 = 0; index2 < sizeStr2; index2++)
		{
			compare = compareStr(str1+index1, str2);
			if(compare)
			{
				newStr[index3] = compare;
				index3++;
			}
		}
	}
	printf("New String: %s", newStr);
	return 0;
}
