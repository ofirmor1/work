#include <stdio.h>
#define NUM_OF_BITS 8
#define MAX_SIZE 5
#define AJUSTED -'a'+1


int SqueezArray(char* _aoArray,int _n) /*ch1= str[0]-'a'+1*/
{
	unsigned char ch1, ch2;
	int j,i,length;
	i=0;
	length = _n/2 + _n%2;
	
	for(j=0; j<length ; j++)  
	{
		ch1 = _aoArray[i]AJUSTED;
		ch1 = ch1 << 4;

		if (i == _n-1)  /*case of _n=1 OR i points to last*/ 
		{
			_aoArray[j] = ch1;
			break;					
		}	
		ch2 = _aoArray[i+1]AJUSTED;
		ch1 = ch1 | ch2;
		_aoArray[j]=ch1;
		i=i+2;


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







