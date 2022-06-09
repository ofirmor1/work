#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_BITS sizeof(char)*8

int CountSetBits(unsigned char _num)
{
	int counter = 0;

	while(_num)
	{
		counter += _num & 1;
		_num >>= 1;
	}
	return counter;
}

int main(void)
{
	int result;
	result = CountSetBits(9);
	printf("num of bits in number: %d\n", result);
	
	return 0;
}
