#include <stdio.h>
#include <stdlib.h>

int main()
{
	char character = 'a';
	int i;
	int abcIndex;
	int ABCIndex = 26;
	char fileName[] = "sample3.txt";
	char abc[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int countChar[52] = {0};
	int c;
	FILE *file;
	if((file = fopen(fileName , "r")) == NULL)
	{
		printf("File could not be opened \n");
		return;
	}
	while(!feof(file))
	{
		c = fgetc(file);
		if(c >= 'a' && c <= 'z')
		{
			abcIndex = c - 'a';
			countChar[abcIndex]++;
		}
		if((c >= 'A' && c <= 'Z'))
		{
			ABCIndex = c - 'A';
			countChar[26+ABCIndex]++;
		}
	}
	for(i = 0; i < 52; i++)
	{
		if(countChar[i] > 0)
		{
		printf("%c %d\n",abc[i] , countChar[i]);
		}
	}
	fclose(file);
}

