#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_OF_BITS sizeof(char)*8
#define INVALID_CHAR -1
#define ARRAY_SIZE sizeof(char)*4

/*
int DemoLang(char _str[])
{
	int index1,index2,index3 = 0;
	int strLen = strlen(_str);
	char NewStr[i]
	for(index1 = 0; index1 < strLen; index1++)
	{
		if(_str[index1] > 'o' || _str < 'a')
		{
			return INVALID_CHAR;
		}
		NewStr[i] = (_str[index1] -'a' + 1);
	}
	for(i = 0; i < strLen-1; i += 2)
	{
		_str[i] = NewStr[index1];
		NewStr[index1 + 1] = NewStr << 4;
		NewStr[index1 + 1] = NewStr[index1 + 1] | NewStr[index1];
		NewStr[index3] = NewStr[index1 + 1];
		index3;
	}
}



/*10100111*/
/*11110100 rotate by 3*/
/*1*2^(n-i) --> n = 7*/
/*128+64+32= 224 --> 11100000*/
/*
void PrintBits(int _number)
{
	int i,bit, arr[NUM_OF_BITS];
	for(i = 0; i < NUM_OF_BITS; i++)
	{
		bit = _number % 2; /*0 0 0 1 1 1 1 1
		_number /= 2;/
		arr[i] = bit;
		
	}	
	for(i = NUM_OF_BITS-1; i >= 0; i--)
	{
		printf("%d ", arr[i]);
		
	}
}
*/
int main()
{
	char _str[] = "abcd";
	int index1,index2,index3 = 0;
	int strLen;
	char NewStr[ARRAY_SIZE];
	strLen= strlen(_str);
	for(index1 = 0; index1 < strLen; index1++)
	{
		if(_str[index1] > 'o' || _str[index1] < 'a')
		{
			return INVALID_CHAR;
		}
		NewStr[index1] = (_str[index1] -'a' + 1);
		printf("%d ", NewStr[index1]);
	}
	printf("\n");
	for(index1 = 0; index1 < strLen-1; index1 += 2)
	{
		_str[index1] = NewStr[index1];
		NewStr[index1 + 1] = NewStr[index1 + 1] << 4;
		NewStr[index1 + 1] = NewStr[index1 + 1] | NewStr[index1];
		NewStr[index3] = NewStr[index1 + 1];
		index3;
		printf("%d ", NewStr[index1]);
		printf("\n");
		printf("%d ", _str[index1]);
	}
	
}
