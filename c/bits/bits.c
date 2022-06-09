#include <stdio.h>
#define NUM_OF_BITS 8



int CheckIfNOn(unsigned char _a, int _n)
{
	unsigned char b;
	int check;

	b = 1;
	b = b << _n;
	check = _a & b;
	
	if(check)
	{
		return 1;
	}

	return 0;
	
}

int CountOnBits(unsigned char _a)
{
	int index;
	int count=0;

	for (index=0 ; index < NUM_OF_BITS ; index++)
	{
		if(CheckIfNOn(_a, index))
		{
			count++;
		}
	}
	return count;

}

int CountOnBitsInt(unsigned int _a)
{
	int index;
	int count=0;

	for (index=0 ; index < NUM_OF_BITS*sizeof(int) ; index++)
	{
		if(CheckIfNOn(_a, index))
		{
			count++;
		}
	}
	return count;

}

int InvertBits(unsigned char _a)
{
	int indexStr, n;
	unsigned char str[NUM_OF_BITS+1]={0};
	
	for (n=NUM_OF_BITS-1, indexStr==0 ; n >= 0 ; n--, indexStr++)
	{
		str[indexStr] = CheckIfNOn((unsigned char)~_a, n) + '0';
				
	}
	
	str[NUM_OF_BITS]='\0';
	printf("%s\n",str);	
}

RoundRotateRight (unsigned char _a, int _n)
{
	int i;
	unsigned char rightBit;
	unsigned char oneOnRightOthersZero=1;
	unsigned char oneOnLeftOthersZero=128;

	
	for (i=0; i<_n; i++)
	{
		rightBit = _a & oneOnRightOthersZero;
		_a = _a >> 1;
		if (rightBit)   /*if different from 0*/
		{
			_a = _a | oneOnLeftOthersZero;
		}				
	}
printf("%d\n", (int)_a);
}


int main (void)
{
	unsigned char a = 5;
	int bitIndex = 2;
	int numOfRotates = 3;

  	printf ("%d\n",CheckIfNOn(a, bitIndex));/*class tar*/
	printf("%d\n" ,CountOnBits(a));/*tar1*/ 
	InvertBits(a);					/*tar2*/  
	RoundRotateRight (a, numOfRotates);/*tar3*/
}




