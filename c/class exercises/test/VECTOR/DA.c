#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NewMemo 1

enum STAT {OK, NULL_ERROR, OVERFLOW, UNDERFLOW, REALLOC_FAIL};

typedef struct 
{
	int *dArray;
	int dArraySize;
	int dArrayBlockSize;
	int numOfElements;
	
}DA;

DA *create(int dArraySize, int dArrayBlockSize) 
{

	DA *ptrStruct;
	int *ptrArray;
	
	
	ptrStruct= (DA*) malloc(sizeof(DA));
	ptrArray= (int*) malloc(sizeof(int)*dArraySize);
	if (NULL == ptrStruct || NULL == ptrArray)
	{
		if(	ptrStruct!= NULL)
		{
			free(ptrStruct);
		}
		else
		{
			free(ptrArray);
		}	
		return NULL;
			
	}	
	
	ptrStruct->numOfElements = 0;
	ptrStruct->dArray = ptrArray;
	ptrStruct->dArraySize = dArraySize;
	ptrStruct->dArrayBlockSize = dArrayBlockSize;
	
	return ptrStruct;
}

void destroy(DA *ptrStruct)
{	
	free(ptrStruct->dArray);
	free(ptrStruct);
}

enum STAT insert(DA *ptrStruct, int data)
{	
	int AddSize;
	int CurrentSize;
	int NewSize;
	int OldSize;
	int *temp;

	if(NULL==ptrStruct)
	{
		return NULL_ERROR;
	}

	AddSize=ptrStruct->dArrayBlockSize;
	OldSize=ptrStruct->dArraySize;
	NewSize=AddSize+OldSize;
	

		if(ptrStruct->dArraySize == ptrStruct->numOfElements)
		{
			
			if(AddSize==0)
			{
				return OVERFLOW;
			}			
			temp= (int*) realloc(ptrStruct->dArray,NewSize*sizeof(int));
			if(NULL==temp)
			{
				return REALLOC_FAIL;		
			}
			ptrStruct->dArray=temp;
			ptrStruct->dArraySize=NewSize;
				
		}
	
	*(ptrStruct->dArray + ptrStruct->numOfElements)=data;
	(ptrStruct->numOfElements)++;
	
}

enum STAT DAremove(DA *ptrStruct, int *data)
{
		if(NULL==ptrStruct)
		{
			return NULL_ERROR;
		}

		if(ptrStruct->numOfElements==0)
		{
			return UNDERFLOW;				
		}
	
	*data= *(ptrStruct->dArray + ptrStruct->numOfElements-1); 
	(ptrStruct->numOfElements)--; 
}
												
int main (void)
{
	DA *ptrStruct;
	int i=0;
	int checkRemove;
		
	ptrStruct = create(3,5);/*create(int dArraySize, int dArrayBlockSize */
	checkRemove = DAremove(ptrStruct,&i);	
	insert(ptrStruct,1);
	insert(ptrStruct,2);
	insert(ptrStruct,3);
	insert(ptrStruct,4);
	
	
	destroy(ptrStruct);

}

