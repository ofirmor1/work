#include <stdio.h>
#include <string.h>

void reverse(char* str, int _length)
{
	int start = 0;
	int end = _length - 1;
	char temp;
	while (start < end)
	{
		temp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = temp;
		start++;
		end++;
	}
}

char* myAtoi(int num, char *str)
{
	int sign = 1;
	int i = 0;
   	if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
	if (num < 0)
	{
		sign = -1;
	}
	while(num != 0)
	{
		str[i++] = num % 10 + '0';
		num = num / 10;	
	}
	if(sign == -1)
	{
		str[i++] = '-';
	}
	str[i] = '\0';
	
	/*reverse(str,i);*/
	
	return str;
}

int main()
{
	int num = 123;
	char str[20];
	char* value = myAtoi(num, str);
	printf("%s\n ", value);
	return 0;
}
