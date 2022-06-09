#include <stdio.h>
#define IS_RETSEF 1
#define NOT_RETSEF 0
/*	char s1[20] = "abcd";
	char s2[20] = "cd";*/
int Location(char *str1,char *str2)
{
	int i= 0, j = 0,location = -1,checkRetsef = NOT_RETSEF;
	while(str2[j] != '\0')
	{
		if (str1[i] != str2[j])
		{
			location = -1;
			i++;
		}
		if(str1[i] == '\0')
		{
			i = 0;
			j++;
		}
		if(str1[i] == str2[j])
			{
				if(checkRetsef == NOT_RETSEF)
				{
					checkRetsef = IS_RETSEF;
					location = i;
					i++;
					j++;
				}
				else
				{
					i++;
					j++;
				}
			}
	}
	if(str1[0] == '\0' && str2[0] == '\0')
	{
		location = 0;
	}
	return location;
}
	
int main(void)
{
	char s1[20] = "";
	char s2[20] = "";
	int match_Location;
	
	match_Location = Location(s1,s2);
	
	printf("%d\n ", match_Location) ;
	
}
