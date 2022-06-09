#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0;
#define SUCCESS 1;


static void GenSwap(void * _e1, void * _e2, size_t _sizeOfElement, void * _temp);

int GenSort(void * _data, size_t _numOfElements, size_t _sizeOfElement, int(*_SortCri)(const void * _e1, const void * _e2))
{
	size_t index, j;
	int flag = 0;
	void *temp = (void*)malloc(_sizeOfElement);	
	if(temp == NULL)
	{
		return ERROR;
	}
	for(j = 0; j < _numOfElements - 1; j++)
	{
		flag = 0;
		for(index = 0; index < _numOfElements -1 -j; index++)
		{
			if(_SortCri((void*)((char*)_data + index*_sizeOfElement),(void*)((char*)_data + (index + 1)* _sizeOfElement)))
			{
				GenSwap((void*)((char*)_data + index*_sizeOfElement),(void*)((char*)_data + (index + 1)* _sizeOfElement), _sizeOfElement, temp);
				flag = 1;
			}
		}
		if(flag == 0)
		{
			break;
		}
	}
		free(temp);
		return SUCCESS;
}

static void GenSwap(void * _e1, void * _e2, size_t _sizeOfElement, void * _temp)
{
	memcpy(_temp, _e1, _sizeOfElement);
	memcpy(_e1, _e2, _sizeOfElement);
	memcpy(_e2, _temp, _sizeOfElement);
}


