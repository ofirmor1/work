#include <stdio.h>

#define ERROR 0

int checkParameters(char *str)
{
	if(str == NULL)
	{
		return ERROR;
	}
}

int skipBlanks(char *str)
{
	int i = 0;
  	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') 
	{
		i++;
	}
	return i;
}

int checkSign(char *str)
{
	int sign;
	int i = skipBlanks(str);
	if (str[i] == '-') 
	{
		sign = -1;
	}
	return sign	;
}

int myAtoi(char* str)
{
	int i,sign,result = 0;
	i = skipBlanks(str);
	sign = checkSign(str);
	if (sign == -1)
	{
	i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		{
			result = result * 10 + (str[i] - '0');
			i++;
			printf("%d\n", result);
		} 
	return result * sign;
}
/*return i = 2*/
/*return i = -1*/
int main()
{
	int value;
	
	char str[] = "  -136!";
	if(checkParameters)
	{
		value = myAtoi(str);
		printf("%d \n", value);
	}
	return 0;
}

