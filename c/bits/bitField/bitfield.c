#include <stdio.h>
#define NUM_OF_BITS 8
#define MAX_SIZE 5
#define AJUSTED -'a'+1

typedef struct Bitfield
{
	unsigned char m_right :4;
	unsigned char m_left :4;	
}Bitfield;

int SqueezArray(char* _aoArray,int _n)
{
	unsigned char ch1, ch2;
	int j,i,length;
	Bitfield* bitfieldPtr;
	
	i=0;
	length = _n/2 + _n%2;

	bitfieldPtr = (Bitfield*)_aoArray;

	for(j=0; j<length ; j++)  
	{
		bitfieldPtr->m_left = _aoArray[i]AJUSTED;
		bitfieldPtr->m_right= _aoArray[i+1]AJUSTED; 
		i=i+2;
				       							
		if (i == _n-1)  
		{
			bitfieldPtr ++;
			bitfieldPtr->m_left = _aoArray[i]AJUSTED;
			bitfieldPtr->m_right= '\0';	
			break;					
		}
		bitfieldPtr ++; 	
	}
	for(i=0;i<length; i++)
	{
		printf("%d\n",_aoArray[i]);
	}
}

int main (void)
{
	char aoArray[MAX_SIZE] = "abcde";
	SqueezArray(aoArray, MAX_SIZE);	
}







