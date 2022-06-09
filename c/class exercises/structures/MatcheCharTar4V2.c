#include <stdio.h>
#define ERROR 0
#define SUCCESS 1


int removechar(char *str, char CharToRemove)
{
	int write=0;
	int read;

	for (read=0; str[read]!='\0';read++)
		{
			if (str[read]!=CharToRemove)
				{
					str[write]=str[read];
					printf("%s\n\n", str);
					write++;
				}
		}
	str[write]='\0';		
} 

/*	char str1[20]= "abcldde";
	char str2[20]= "ad";*/

int compareArray(char *str1,char *str2)
{
	int j=0;
	char CharToRemove;
	
	while (str2[j]!='\0')
	{
		CharToRemove=str2[j];
		removechar(str1,CharToRemove);
		j++;
	}
}	





int main (void)
{
	char str1[20]= "abcldde";
	char str2[20]= "ad";
	int comp;

	comp= compareArray(str1,str2);

	printf("%s\n",str1);
	
}

	



