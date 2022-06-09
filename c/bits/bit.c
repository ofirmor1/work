#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_BITS sizeof(char)*8

int CheckBitStatus(unsigned char _bit ,int _number)
{
	if ((_number & (1 << _bit)) == 0)
	{
		return 0;

	}
	else
	{
		return 1;
	}		
}

int CountSetBits(int _numOfBits, int _number)
{
	int i, counter = 0;
	for(i = 0; i < _numOfBits; i++)
	{
		if (CheckBitStatus(i, _number) == 1)
		counter++;
	}	
	return counter;
}
/*int argc, char* argv[]*/
int main()
{
	int number = 2; /*18*/
	unsigned char bit = 2;
	int counter = CountSetBits(bit,number);
	if(CheckBitStatus(bit, number) == 1)
	{
	printf("Bit number %d is SET in number %d.\n",bit, number);
	}
	else
	{
	printf("Bit number %d is not SET in number %d.\n",bit, number);
	}
	counter = CountSetBits(NUM_OF_BITS, number);
	printf("%d\n", counter);
	
}
