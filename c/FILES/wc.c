#include <stdio.h>
#include <string.h>
#define FILE_NOT_FOUND 0
#define MAX_CHAR_IN_LINE 500
#define FILE_NOT_CLOSE 1

int CountWords (char *_str)
{
	int i=0;
	int countWord=0;
	
	while (_str[i] != '\0' && _str[i] != '\n')
	{
		if((_str[i]!= '\t' && _str[i]!= ' ') && (_str[i+1]== '\t' || _str[i+1]== ' '||
          _str[i+1]== '\0'))
		{
			countWord++;			
		}
		i++;
	} 
	return countWord;
}
/********************************************************/
int WcFunc ()
{
	int numOfLines, numOfwords, numOfChars;
	char str[MAX_CHAR_IN_LINE];
	int checkScanf;

	FILE * fp = fopen("person_file", "r");
	if(fp == NULL)
	{
		return FILE_NOT_FOUND;
	}
	numOfLines = 0;
	numOfwords = 0;
	numOfChars = 0;
	

	while (fgets(str,MAX_CHAR_IN_LINE,fp) != NULL)
	{					
		printf("%s\n",str);	
		numOfwords += CountWords(str);				
		numOfLines++;			
	}

	fseek (fp,0,SEEK_END);
	numOfChars = ftell(fp);

	printf("numOfLines %d \n",numOfLines);
	printf("numOfwords %d \n",numOfwords);
	printf("numOfChars %d \n",numOfChars);
	
	if(fclose(fp) != 0)
	{
		return FILE_NOT_CLOSE;
	}
		 
}
/********************************************************/
int main (void)
{

	char fileName[20]= "person_file";
	WcFunc();



}
