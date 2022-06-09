#include <stdio.h>
#include <stdlib.h>
#define FILE_NOT_FOUND 0

int PrintLinesFromTail(int _n, FILE* _fp)
{
	int countLines = 0;
	int a;
	if(_fp == NULL)
	{
		return FILE_NOT_FOUND;
	}
	fseek(_fp,-1,SEEK_END);
	if(fgetc(_fp) == '\n')
	{
		countLines++;
	}
	while(countLines < _n)
	{
		fseek(_fp,-1,SEEK_CUR);
		if(fgetc(_fp) == '\n')
		{
			countLines++;
			printf("%d\n", fgetc(_fp));
		}
	}
	printf("%d\n", countLines);
	printf("%d\n", _n);
	printf("%d\n", fgetc(_fp));
	printf("%ld\n", ftell(_fp));
}
int main()
{
	FILE *cfPtr;
	if((cfPtr = fopen("persons.txt" , "r")) == NULL)
	{	
	printf("File could not be opened 				\n");
	}
	else
	{
		PrintLinesFromTail(2, cfPtr);
	}
	
}
