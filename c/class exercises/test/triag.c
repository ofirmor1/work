#include <stdio.h>
#define SUCCESS 0
#define SIZE_ERROR 1
#define CHAR_ERROR -1
#define MIN_SIZE 2
#define MAX_SIZE 40
#define MIN_CHAR !
#define MAX_CHAR ~
 
 int printCharLine(int n, char ch,int _offSetNum)
 {
 	int i;
 	for (i = 0; i < n; i++)
 	{
 		putchar(ch);
 		if(_offSetNum > 0)
 		{
 			(' ');
 		}
 	}
 }
 
  int printTriangle(int n, char ch, int _offSetNum)
 {
 	int i;
 	for(i = 0; i < n; i++)
 	{
 		printCharLine(i,ch,_offSetNum);
 		putchar('\n');
 	}
 } 
 
 int printTriangleOffset(int n, char ch, int _offSetNum)
 {
 	int i;
 	for (i = n; i >= 0; i--)
 	{
		printCharLine(i,ch,_offSetNum);
 	}
 } 
 
 int checkParameters(int n, char ch)
 {
 	if ((n < MIN_SIZE) || (n > MAX_SIZE))
 	{
 		return SIZE_ERROR;
 	}
 	if ((ch < '!') || (ch > '~'))
 	{
 		return CHAR_ERROR;
 	}
 	
 	return SUCCESS;
 }

int func1(int n, char ch,int _offSetNum)
{
	int i;
	int checkParamStatus;
	if(checkParamStatus = (checkParameters(n, ch) != SUCCESS))
	{
		return checkParamStatus;
	}
	printTriangle(n, ch, _offSetNum);
	return SUCCESS;
}

int func2(int n, char ch,int _offSetNum)
{
	int i;
	int checkParamStatus;
	if(checkParamStatus = (checkParameters(n, ch) != SUCCESS))
	{
		return checkParamStatus;
	}	
	printTriangleOffset(n, ch, _offSetNum);
	return SUCCESS;
}

int func3(int n, char ch,int _offSetNum)
{
	int i;
	int checkParamStatus;
	if(checkParamStatus = (checkParameters(n, ch) != SUCCESS))
	{
		return checkParamStatus;
	}
	
	printTriangle(n, ch, _offSetNum);
	printTriangleOffset(n, ch, _offSetNum);
	return SUCCESS;
}


