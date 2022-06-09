#include <stdio.h>
#include "myitoa.h"

void swap(char num1, char num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

/*reverse a string */
void Reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap(*(str + start), *(str + end));
        start++;
        end--;
    }
}
 
char* Itoa(int num, char* str)
{
    int i = 0;
    int isNegative = 0;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    if (num < 0)
    {
        isNegative = 1;
        num = -num;
    }
 
    while (num != 0)
    {
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
 
    if (isNegative == 1)
    {
        str[i++] = '-';
    }
 
    str[i] = '\0';
    Reverse(str, i);
 
    return str;
}
 
/*
int main()
{
	int value, num, *ptr;
	
	num = 14567;
	ptr = (char*)malloc(100*sizeof(char));
	if(checkParameters)
	{
		value = myAtoi(str);
		printf("%d \n", value);
	}
	return 0;
}
*/
