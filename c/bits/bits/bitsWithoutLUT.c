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
unsigned int Reverse(unsigned int _num)
{
	static int index;
	unsigned int revNum = 0;

    for(index = 0; index < sizeof(int)*8+1; index++)
    {
        revNum <<= 1;
        if(_num & 1 == 1)
        {
            revNum |= 1;
        }
        _num >>= 1;
        /*printf("\n_num = \n");
		printBits(_num);*/
    }
	return revNum;
}
/****************************************************************/
unsigned int SwapPairBits(unsigned int _num)
{

    return (((_num << 1) & 0xAAAAAAAA) | (_num >> 1) & 0x55555555 );
}
/****************************************************************/
unsigned int offsetOf3thBitOn(unsigned int _num)
{
    static int index;
	unsigned int numOfSetBits = 0;

    for(index = 0; index < sizeof(int)*8+1; index++)
    {
        if(_num & 1 == 1)
        {
            numOfSetBits++;
        }
        _num >>= 1;
        if(numOfSetBits == 3)
        {
            return index;
        }
    }
    
    return -1;
}


/*input 2 numbers:
return tru if a > b
false otherwise. no use condition.*/


/*5 - 0000000000000101
  3 - 0000000000000011
  2 - 0000000000000010
 -2 - 1111111111111110
  0100010101*/
/****************************************************************/
int Larger(int _a, int _b)
{	
	int larger;
	larger = _a - _b; /*1 - a larger, 0 - b larger*/
    return CheckPositive(larger);
}
/****************************************************************/
int CheckPositive(int _num)
{ 
    return ((_num >> 31) & 1) ^ 1;
}
/****************************************************************/
int main()
{
    int number = 7;
    printf("reversed number(answer in decimal):  %u\n" , Reverse(5640));
    printf("Swapped pair bits in number(answer in decimal): %u\n" , SwapPairBits(50));
    printf("The offset of 3th bit ON in number %d: %u\n" , number, offsetOf3thBitOn(number));
    printf("sign of int %d (1 - positive, 0 - negative) : %u\n" , number, CheckPositive(number));
    printf("Is a > b ? (1 - True, 0 - False) : %d\n", Larger(5 ,3));
    


    return 0;
}
