#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ADTDefs.h"
#include "Vector.h"
#define NUM_OF_ELEMENTS 7


ADTErr CheckParameters(Vector* _vec , size_t _numOfElements)
{
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_numOfElements == 0)
	{
		return ERR_IS_EMPTY;
	}
return ERR_OK;
}

/******************************************************************************/
void Swap(Vector* _vec ,size_t _i ,size_t _j)
{	
	int n1, n2, temp;

	VectorGet(_vec, _i , &n1);
	VectorGet(_vec, _j , &n2);
	
	temp= n1;
	VectorSet(_vec, _i, n2);	
	VectorSet(_vec, _j , temp);		
}
/******************************************************************************/
ADTErr BubbleVector (Vector* _vec , size_t _numOfElements)
{
	int n1,n2, flag;
	size_t i,j;
	i=0;

	if(!(CheckParameters (_vec , _numOfElements) == ERR_OK))
	{
		return ERR_ERROR;
	}

	for (j=0 ; j < _numOfElements-1; j++)
	{
		flag=0;
		for (i=0 ; i<_numOfElements-1-j ; i++)
		{
			VectorGet(_vec, i , &n1);
			VectorGet(_vec, i+1 , &n2);
			if (n1> n2)
			{
				Swap(_vec , i, i+1);
				flag = 1;
			}
		}
		if (flag ==0)
		{
			return ERR_OK;
		}
	}
	return ERR_OK;
}
/******************************************************************************/
int StartToEnd(Vector* _vec, size_t _index , int _stopPoint)
{
	int n1, n2 , flag;
	flag=0;
	while (_index < _stopPoint)
	{
		VectorGet(_vec, _index , &n1);
		VectorGet(_vec, _index+1 , &n2);
		if (n1 > n2)
		{
			Swap(_vec , _index, _index+1 );
			flag = 1;
		}
		_index++;		
	}
return flag;	
}

int endToStart(Vector* _vec, size_t _index , int _stopPoint)
{
	int n1, n2 , flag;
	flag=0;

	while (_index > _stopPoint)
	{
		VectorGet(_vec, _index-1 , &n1);
		VectorGet(_vec, _index , &n2);
		if (n1 > n2)
		{
			Swap(_vec , _index-1, _index);
			flag = 1;
		}
		_index--;		
	}
return flag;	
}
/******************************************************************************/
ADTErr ShakeVector (Vector* _vec , size_t _numOfElements)
{
	int n1,n2;
	size_t i,j;
	i=0;

	if(!(CheckParameters (_vec , _numOfElements) == ERR_OK))
	{
		return ERR_ERROR;
	}

	for (j=0 ; j<_numOfElements/2 ; j++)
	{
		if(!(StartToEnd(_vec, j , _numOfElements-1-j)))
		{
			return ERR_SORTED;
		}		
		if(!(endToStart(_vec, _numOfElements-2-j , j)))
		{
			return ERR_SORTED;
		}		
	}
}
/******************************************************************************/
size_t Partition (Vector* _vec, size_t _startIndex , size_t _endIndex)
{
	int pivot,j,i;
	int curValue;
    VectorGet(_vec, _endIndex, &pivot);
    i = _startIndex-1;	
    for (j = _startIndex; j <= _endIndex - 1; j++) 
    { 
    	VectorGet(_vec, j, &curValue);
        if (curValue < pivot) 
        { 
            _startIndex++;
            Swap(_vec, i, j); 
        } 
    } 
    Swap(_vec, i + 1, _endIndex); 
    return (i+1); 		
}
/******************************************************************************/
int Quik (Vector* _vec , int _low, int _high)
{	
	if (_low < _high) 
    { 
        int parIndex = Partition(_vec, _low, _high); 
        Quik(_vec, _low, parIndex - 1); 
        Quik(_vec, parIndex + 1, _high); 
    }
}

/******************************************************************************/
/*
void heapSort(Vector* _vec, int n)
{	
	int i;
	for(i = n/2 - 1; i >=0; i--)
	{
		heapify(_vec, n, i);
	}
	for( i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(_vec, i, 0);
	}
}
/*Create maxs heap*/
/*Swap first and last node*/
/*Create max heap on reduced array*/

/******************************************************************************/
void Insertion(Vector* _vec, size_t _numOfElements)
{
    int i, j, n1, n2;
    
    for (i = 1; i < _numOfElements; i++) 
    {
        VectorGet(_vec, i, &n1);
        j = i - 1;
        VectorGet(_vec, j, &n2);
        while (j >= 0 && n2 > n1) 
        {
        	Swap(_vec, j, j+1);
            j = j - 1;
            VectorGet(_vec, j+1, &n1);
        	VectorGet(_vec, j, &n2);
        }
        VectorSet(_vec, j + 1, n1);
    }
}
/******************************************************************************/
/*18 49 64 31 17 5 102 41 83 2 46
gap = 5*/
void shell(Vector* _vec, size_t _numOfElements)
{
	int i, j, temp, dataLeft, g;
    for (g = _numOfElements/2; g > 0; g /= 2)
    {
        for (int i = g; i < _numOfElements; i++)
        {
        	VectorGet(_vec, i, &temp);
            for (j = i; j >= g && arr[j - gap] > temp; j -= gap)/* j = 5*/
            {	
          		VectorGet(_vec, j, &dataLeft);
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return 0;
}

void Merge(Vector* _vec,int* temp, size_t _start,size_t end, size_t mid)
{
	int indexFirstArray;
	int indexFirstArray;
	
	while(i <=
}
/******************************************************************************/
int main (void)
{
	int i, randNum;
	clock_t t1, t2;
	Vector* vecPtr;
	int array[NUM_OF_ELEMENTS]= {3,5,2,4,8,9,1};
	
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array[i]);
	}
	t1=clock();
	BubbleVector (vecPtr , NUM_OF_ELEMENTS);
	t2=clock();
	printf("BubbleVector: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	/*VectorPrint(vecPtr);*/
	printf("******************************\n");
/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array[i]);
	}
	t1=clock();
	ShakeVector(vecPtr , NUM_OF_ELEMENTS);
	t2=clock();
	printf("ShakeVector: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	/*VectorPrint(vecPtr);*/
/*******************************************************/
	/*=*vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array[i]);
	}
	t1=clock();
	Quik(vecPtr , 0, NUM_OF_ELEMENTS-1);
	t2=clock();
	printf("Quik: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	VectorPrint(vecPtr);*/
/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array[i]);
	}
	t1=clock();
	Insertion(vecPtr, NUM_OF_ELEMENTS);
	t2=clock();
	printf("Insertion: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	VectorPrint(vecPtr);
	
	return 0;
}

