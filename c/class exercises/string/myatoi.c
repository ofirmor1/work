#include <stdio.h>

int myAtoi(char* str)
{
	int result = 0;
	int sign = 1;
	int i = 0;
  	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') 
  		{
  			i++;
		}
	if (str[i] == '-') 
		{
			sign = -1;
			i++;
		}
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		{
			result = result * 10 + (str[i] - '0');
			i++;
			printf("%d\n", result);
		} 
	return sign * result;
}

int main()
{
	char str[] = "  -136!";
	int value = myAtoi(str);
	printf("%d ", value);
	return 0;
}

