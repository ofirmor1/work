#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_BITS sizeof(char)*8

void PrintBits(int _number)
{
	int i,bit, arr[NUM_OF_BITS];
	for(i = 0; i < NUM_OF_BITS; i++)
	{
		bit = _number % 2; /*0 0 0 1 1 1 1 1*/
		_number /= 2;/*7 3 1 0 */
		arr[i] = bit;
		
	}	
	for(i = NUM_OF_BITS-1; i >= 0; i--)
	{
		printf("%d ", arr[i]);
		
	}
}
int InvertBits(int _number)
{
	int i;
	for(i = 0; i < NUM_OF_BITS; i++)
	_number ^= (1 << i);
	return _number;
	/*printf("%d\n ", _number);/*7 --> 248*/
}
/*int argc, char* argv[]*/
int main()
{
	int number = 7;/*1 1 1 0 0 0 0 0*/
	InvertBits(number);
	printf("x = ");
	PrintBits(number);
	printf("\ny = ");
	PrintBits(InvertBits(number));
	printf("\n");
}
