#include <stdio.h>
#include <stdlib.h>
#define NO_OF_BITS 8
#define POSSIBLE_VALUES 256
#define POSSIBLE_PAIR_BITS 4

void printBits(unsigned int _num)
{
	int bit;
	for(bit = 0;bit < (sizeof(unsigned int) * 8); bit++)
	{
		if ( bit == 8 || bit == 16 || bit == 24)
		{
			printf("|");
		}
		printf("%i ", _num & 0x01);
		_num = _num >> 1;
	}
}

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

void BuildLUT(unsigned char *_cb)
{
	int i;
	for( i = 0; i < 256; ++i)
	{
		_cb[i] = CountSetBits(i);
	}	
}

void BuildPairBitsLUT(unsigned char *_cb)
{
	int j, i ;
	for(j = 0; j < 256; j++)
	{	
		j &= 0xff;
		/*printf("befor %d\n", j);*/
		_cb[j] =	((j & 0xAA) >> 1) | ((j & 0x55) << 1);
		/*printf("after %d\n", _cb[j]);*/
	}
}

void BuildReversedBitsLUT(unsigned char *_cb)
{
	int i, j, reversedNum = 0;
	for(j = 0; j < 256; j++)
	{	
		reversedNum = 0;
 		for (i = 0; i < NO_OF_BITS; i++)
    	{
        	if((j & (1 << i)))
        	{
        	reversedNum |= 1 << ((NO_OF_BITS - 1) - i); 
        	}

   		}
   		_cb[j] = reversedNum;
   		/*printf("%d ,",  _cb[j]);*/
	}	
}

unsigned char CountBitsByLUTInt(unsigned int _num)
{
	static int index, result, sum;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		BuildLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int))
	{
		result = _num & 0xff;
		sum += charBits[result];
		_num >>= NO_OF_BITS;
		index++;
	}
	printf("%d \n",  sum);
	return sum;
}

int CountBitsByLUT(unsigned char _num)
{
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		BuildLUT(charBits);
		flag = 1;
	}
	return charBits[_num];
}

/*
	int reversed_byte = 0;
	int bit_value;
  for (bit_index = 0; bit_index < 8; bit_index++) 
  {
    bit_value = (num >> bit_index) & 1;
    reversed_byte |= bit_value << (7 - bit_index);
  }
*/

/*(1<< & result)
for(;i<sizeof(int);i++)
{
	result |= (unsigned int)(revcb[_num & 255] << 		((sizeof(int)-i-1) * CHAR_SIZE));
		_num >>= 8;
}
*/

unsigned char Reverse(unsigned int _num)
{
	static int index = 1;
	unsigned int reversedByte = 0, result;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		BuildReversedBitsLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int))
	{
        result = _num & 0xff;
		reversedByte |= charBits[result];
		printf("%d \n",  reversedByte);
		reversedByte <<= NO_OF_BITS;
		/*printf("%d ,",  reversedByte);*/
		_num>>=NO_OF_BITS;
		index++;
	}
	printf("%d \n",  reversedByte);
	return reversedByte;
}

unsigned char SwapPairBits(unsigned int _num)
{
	static int index = 1;
	unsigned int SwappedPairBitsInByte = 0, result = 0, swappedNum = 0;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		BuildPairBitsLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int))
	{
		printf("\nnum = \n");
		printBits(_num);
        result =_num & 0xff;
        printf("\nresult = \n");
        printBits(result);
		SwappedPairBitsInByte = charBits[result];
		printf("\nSwappedPairBitsInByte = \n");
		printBits(SwappedPairBitsInByte);
		_num >>= NO_OF_BITS;
		printf("\n_num after 8 bits moves = \n");
		printBits(_num);
		SwappedPairBitsInByte <<= NO_OF_BITS * index;
		printf("\nSwappedPair after 8 bits moves = \n");
		printBits(SwappedPairBitsInByte);
		swappedNum |= SwappedPairBitsInByte | _num;
		printf("\nswappedNum = \n");
		printBits(swappedNum);
		_num >>= NO_OF_BITS;
		index++;
	}
	printf("\n\n");
	return swappedNum;
}/*
	  0110100000100000100101
num - 1100101011100101
result - 11100101
charBits[result] - 11011010
SwappedPairBitsInByte - 11011010
num - 11001010
swappedNum - 1101101000000000
		   ||0000000011011010

num - 11001010
result - 11001010
charBits[result] - 11000101
SwappedPairBitsInByte - 11000101
num - 00000000
swappedNum -*/


/*
1011000001000
10100100000100
0100110100  308
1000111000   568
*/

int main()
{
	static unsigned char charBits[POSSIBLE_VALUES];
	printf("number of bits set in char: %u\n" , CountBitsByLUT(7));
	printf("number of bits set in char: %u\n" , CountBitsByLUTInt(1344));
	printf("reversed number:  %u\n" , Reverse(3));
	printf("Swapped pair bits: %u\n" , SwapPairBits(5640));
	/*BuildPairBitsLUT(charBits);*/
	
	return 0;
}
