#include <stdio.h>
#include <stdlib.h>
#define NO_OF_BITS 8
#define POSSIBLE_VALUES 256
#define POSSIBLE_PAIR_BITS 4

/****************************************************************/
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
/****************************************************************/
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
/****************************************************************/
void CountBitsLUT(unsigned char *_cb)
{
	int i;
	for( i = 0; i < 256; ++i)
	{
		_cb[i] = CountSetBits(i);
	}	
}
/****************************************************************/
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
/****************************************************************/
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
/****************************************************************/
unsigned char CountBitsByLUTInt(unsigned int _num)
{
	static int index, result, sum;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		CountBitsLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int))
	{
		result = _num & 0xff;
		sum += charBits[result];
		_num >>= NO_OF_BITS;
		index++;
	}
	
	return sum;
}
/****************************************************************/
int CountBitsByLUT(unsigned char _num)
{
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		CountBitsLUT(charBits);
		flag = 1;
	}
	return charBits[_num];
}
/****************************************************************/
unsigned int Reverse(unsigned int _num)
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
		/*printf("\noriginal num = \n");
		printBits(_num);*/
        result = _num & 0xff;
        /*printf("\nresult = \n");
		printBits(result);*/
		reversedByte |= charBits[result];
		/*printf("\nreversedByte = \n");
		printBits(reversedByte);*/
		reversedByte <<= NO_OF_BITS;
		/*printf("\nreversedByte = \n");
		printBits(reversedByte);*/
		_num >>= NO_OF_BITS;
		/*printf("\n_num after shift8 = \n");
		printBits(_num);*/
		index++;
	}
	return reversedByte;
}
/****************************************************************/
unsigned int SwapPairBits(unsigned int _num)
{
	static int index = 1;
	unsigned int SwappedPairBitsInByte = 0, temp = 0;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		BuildPairBitsLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int) && (_num != 0))
	{
        temp =_num & 0xff;
        SwappedPairBitsInByte |= charBits[temp] << NO_OF_BITS*(index-1);
		_num >>= NO_OF_BITS;
		index++;
	}
	
	return SwappedPairBitsInByte;
}
/****************************************************************/
unsigned int offsetOf3thBitOn(unsigned int _num)
{
	static int index = 1;
	unsigned int offset = 0, result = 0, sum = 0;
	static unsigned char charBits[POSSIBLE_VALUES];
	static char flag;
	if(!flag)
	{
		CountBitsLUT(charBits);
		flag = 1;
	}
	while(index < sizeof(int))
	{
		result = _num & 0xff;
		sum += charBits[result];
		if(sum < 3)
		{
			_num >>= NO_OF_BITS;
			offset += 7;
		}
		else
		{
				
		}
		index++;
	}
	return offset;
}
/****************************************************************/
int main()
{
	static unsigned char charBits[POSSIBLE_VALUES];
	printf("number of bits set in char: %u\n" , CountBitsByLUT(7));
	printf("number of bits set in char: %u\n" , CountBitsByLUTInt(1344));
	printf("reversed number(answer in decimal):  %u\n" , Reverse(5640));
	printf("Swapped pair bits in number(answer in decimal): %u\n" , SwapPairBits(5640));
	/*BuildPairBitsLUT(charBits);*/
	
	return 0;
}
