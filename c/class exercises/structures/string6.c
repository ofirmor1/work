#include <stdio.h>

/*	s1 = "Hello World"
	s2 = "eod"
*/
char* replaceStr(char *str1,char *str2)
{
	int i = 0, j = 0;
	while(*(str2+j) != '\0')
	{
			if(*(str1+i) == *(str2+j))
			{
				*(str1+i) = '*';
			}
			if(*(str1+i) == '\0')
			{
				i = 0;
				j++;
			}
			i++;
/*			if(*(str1+i) != *(str2+j))
			{
				i++;
			}*/

	}
	return str1;
}
	
int main(void)
{
	char s1[20] = "Hello World";
	char s2[20] = "eod";
	replaceStr(s1,s2);
	
	printf("%s\n ", s1) ;
	
}
