#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_BITS sizeof(char)*8

/*10100111 -- 167*/
/*11110100*/
/*11110100 rotate by 3*/
/*1*2^(n-i) --> n = 7*/
/*128+64+32= 224 --> 11100000*/

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
/*10100111 -- 167*/
/*11110100*/
int RotateBit(int _num, int n)/*n bits position to rotate*/
{
	int i;
	unsigned char rightBit;
	unsigned char bit1 = 1;/*00000001*/
	unsigned char bit128 = 128;/*10000000*/
	for(i = 0;  i < n; i++)
	{
		rightBit = _num & bit1;
		_num = _num>>1;
		if(rightBit)
		{
			_num = _num | bit128;
		}
	}
	return _num;	
	
}
int main()
{
	int rotatedNum, shiftedBits;
	int num = 167;/*1 1 1 0 0 0 0 0*/
	int rotate = 3;
	printf("x = ");
	PrintBits(num);
	rotatedNum = RotateBit(num, rotate);
	printf("\nx rotated by %d = ", rotate);
	PrintBits(rotatedNum);
	printf("\n");
}
