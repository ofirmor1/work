#include <stdio.h>

int Location(char *s1, char *s2)
{
	int compare, i,j = 0;
	while (s2[j] != '\0')
	{
		for(i = 0; s1[i] != '\0'; i++)
		{
			if(s1[i] == s2[j])
			{
				compare = compareArray(s1,s2,i,j);
			}
		}
		j++;
	}
	return -1;
}

int compareArray(char *str1,char *str2, int s1Index, int s2Index)
{
	int j=0;
	char CharToRemove;
	int Location = s1Index;
	
	while (str1[s1Index] == str2[s2Index])
	{
		s1Index++;
		s2Index++;
		if(str2[s2Index] == '\0')
		{	
			return Location;
		}
	}
}	

int main(void)
{
	char s1[20] = "abcde";
	char s2[20] = "bc";
	int index;
	
	index = Location(s1,s2);
	
	printf("%d\n ", index);
	
}
