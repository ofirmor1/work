#include <stdio.h>
#include <stdlib.h>

void PrintCharsCounting(char *_abc, int *_countChar)
{
	int i;
	for(i = 0; i < 52; i++)
	{
		if(_countChar[i] > 0)
		{
		printf("%c %d\n",_abc[i] , _countChar[i]);
		}
	}	
}

void CountChars(FILE* _file, int *_countChar)
{
	int c;
	int abcIndex;
	int ABCIndex = 26;
	while(!feof(_file))
	{
		c = fgetc(_file);
		if(c >= 'a' && c <= 'z')
		{
			abcIndex = c - 'a';
			_countChar[abcIndex]++;
		}
		if((c >= 'A' && c <= 'Z'))
		{
			ABCIndex = c - 'A';
			_countChar[26+ABCIndex]++;
		}
	}
}

int main()
{
	char character = 'a';
	char fileName[] = "sample3.txt";
	char abc[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int countChar[52] = {0};
	FILE *file;
	if((file = fopen(fileName , "r")) == NULL)
	{
		printf("File could not be opened \n");
		return;
	}
	CountChars(file, countChar);
	PrintCharsCounting(abc, countChar);
	fclose(file);
}
