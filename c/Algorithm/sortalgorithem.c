#include <stdio.h>
#include "Vector.h"
#include <time.h>
#include "ADTDefs.h"
#include <stdlib.h>
#define NUM_OF_ELEMENTS 50000
#define NUM_OF_DIGITS	9

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
void SwapArray(int* _array ,size_t _i ,size_t _j)
{	
	int temp;
	temp= _array[_i];
	_array[_i]=	_array[_j];
	_array[_j]=temp;
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
/******************************************************************************/
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
			Swap(_vec , _index-1, _index );
			flag = 1;
		}
		_index--;		
	}
return flag;	
}
/******************************************************************************/
ADTErr ShakeVector (Vector* _vec)
{
	int n1,n2;
	size_t i,j,numOfElements;
	i=0;

	VectorItemsNum(_vec,&numOfElements);
	if(!(CheckParameters (_vec ,numOfElements) == ERR_OK))
	{
		return ERR_ERROR;
	}

	for (j=0 ; j<numOfElements/2 ; j++)
	{
		if(!(StartToEnd(_vec, j , numOfElements-1-j)))
		{
			return ERR_SORTED;
		}		
		if(!(endToStart(_vec, numOfElements-2-j , j)))
		{
			return ERR_SORTED;
		}		
	}
}
/******************************************************************************/
size_t Partition (Vector*_vec, size_t _startIndex , size_t _endIndex)
{

	int pivot, endVal, startVal, pivotIndex;
	
	pivotIndex = _startIndex;
	VectorGet(_vec, _startIndex , &pivot);
	startVal=pivot;
	

	while (_endIndex > _startIndex)
	{
		while (startVal <= pivot && _startIndex<=_endIndex)
		{
			_startIndex++;
			VectorGet(_vec, _startIndex , &startVal);
		}

		VectorGet(_vec, _endIndex , &endVal);
		while (endVal > pivot)
		{
			_endIndex --;
			VectorGet(_vec, _endIndex , &endVal);
		}

		if (_endIndex > _startIndex)
		{
			Swap(_vec ,_startIndex , _endIndex);
			VectorGet(_vec, _startIndex , &startVal);
			VectorGet(_vec, _endIndex , &endVal);
		}
	}
	Swap(_vec ,pivotIndex , _endIndex);
	return _endIndex;		
}
/******************************************************************************/
ADTErr Quick (Vector* _vec , size_t _startIndex , size_t _endIndex)
{
	size_t posOfPivot, temp;

	if (_startIndex < _endIndex)
	{
		posOfPivot = Partition (_vec,_startIndex ,_endIndex);

		if(posOfPivot >= 1)
		{	
			Quick (_vec , _startIndex , posOfPivot-1);
		}  
			Quick (_vec , posOfPivot +1 , _endIndex);
	}
	
	return ERR_SORTED;	
}
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
void Shell(int *_array , size_t _numOfElements)
{
	int gap;
	size_t i, j;
	int ni, nj;

	for (gap = _numOfElements/2; gap>0; gap=gap/2)
	{
		for (i=0; i+gap < _numOfElements; i++)
		{
			if(_array[i] > _array[i+gap])
			{
				SwapArray(_array , i , i+gap);
				for (j=i; j>=gap &&  _array[j] < _array[j-gap] ; j= j-gap)
				{
					SwapArray(_array , j , j-gap);					
				}

			}
		}
	}
}
/******************************************************************************/
void ShellVector(Vector* _vec , size_t _numOfElements)
{
	int gap;
	size_t i, j;
	int ni, nIPlusGap, nj, nJMinusGap;

	for (gap = _numOfElements/2; gap>0; gap=gap/2)
	{
		for (i=0; i+gap < _numOfElements; i++)
		{
			VectorGet(_vec, i, &ni);
			VectorGet(_vec, i+gap, &nIPlusGap);
			
			if(ni > nIPlusGap)
			{
				Swap(_vec , i , i+gap);

				VectorGet(_vec, i, &ni);
				VectorGet(_vec, i+gap, &nIPlusGap);
				nj=ni;
				VectorGet(_vec, i-gap, &nJMinusGap);
				for (j=i; j>=gap &&  nj < nJMinusGap ; j= j-gap)
				{
					VectorGet(_vec, j, &nj);
					VectorGet(_vec, j-gap, &nJMinusGap);

					Swap(_vec , j , j-gap);					
				}

			}
		}
	}
}
/******************************************************************************/
void Selection (int* _array, size_t _numOfElements)
{
	size_t i, j;
	int  minIndex;

	for (j=0 ; j<_numOfElements; j++)
	{
		minIndex = j;
		for (i=j+1; i<_numOfElements ; i++)
		{		
			if (_array[i] < _array[minIndex])
			{
				minIndex = i;
			}			
		}
		SwapArray(_array, j, minIndex);
	}
	
}

/******************************************************************************/
void SelectionVector (Vector* _vec, size_t _numOfElements)
{
	size_t i, j;
	int  minIndex,arrayi,arrayMinIndex;

	for (j=0 ; j<_numOfElements; j++)
	{
		minIndex = j;
		for (i=j+1; i<_numOfElements ; i++)
		{	
			VectorGet(_vec, i, &arrayi);
			VectorGet(_vec, minIndex, &arrayMinIndex);
				
			if (arrayi < arrayMinIndex)
			{
				minIndex = i;
			}			
		}
		
		Swap(_vec, j, minIndex);
	}	
}
/******************************************************************************/
void MergeArray(Vector* _vec,int* _tempArray, size_t _leftIndex ,size_t _rightIndex)
{
	size_t mid, leftArrayIndex, rightArrayIndex; 	
	size_t tempArrayIndex;
	int startArray, endArray;
	mid = (_rightIndex+ _leftIndex)/2; 
	tempArrayIndex = _leftIndex;
	leftArrayIndex = _leftIndex;
	rightArrayIndex = mid+1;
	
	VectorGet(_vec, leftArrayIndex, &startArray);
	VectorGet(_vec, rightArrayIndex, &endArray);

	while (leftArrayIndex <= mid && rightArrayIndex<=_rightIndex)
	{

		if(startArray >= endArray)
		{
			_tempArray[tempArrayIndex] = endArray;
			rightArrayIndex++;
		}
		else
		{
			_tempArray[tempArrayIndex] = startArray;
			leftArrayIndex++;
		}
		tempArrayIndex ++;
	}

		while (leftArrayIndex<=mid)
		{
			VectorGet(_vec, leftArrayIndex, &startArray);
			_tempArray[tempArrayIndex] = startArray;
			leftArrayIndex++;
			tempArrayIndex++;
		}	

		while (rightArrayIndex<=_rightIndex)
		{
			VectorGet(_vec, rightArrayIndex, &endArray);
			_tempArray[tempArrayIndex] = endArray;
			rightArrayIndex++;
			tempArrayIndex++;
		}

		for (tempArrayIndex=_leftIndex; tempArrayIndex<= _rightIndex;
			 tempArrayIndex++)
		{
			VectorSet(_vec, tempArrayIndex, _tempArray[tempArrayIndex]);
		}					
}

/******************************************************************************/
void RecMergeArray(Vector* _vec,int* _tempArray,size_t _leftIndex ,size_t _rightIndex)
{
	size_t mid;
	if (_leftIndex >= _rightIndex)
	{
		return;
	}
	
	mid = (_rightIndex+ _leftIndex)/2; 
	RecMergeArray(_vec, _tempArray, _leftIndex ,mid);
	RecMergeArray(_vec,_tempArray,mid+1  ,_rightIndex);	
	MergeArray(_vec, _tempArray,_leftIndex ,_rightIndex);

}

/******************************************************************************/
ADTErr MergSort(Vector* _vec)
{
	int* tempArrayPtr;
	size_t numOfElements;
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfElements);
	if (numOfElements ==0)
	{
		return ERR_IS_EMPTY;
	}

	if (numOfElements ==1)
	{
		return ERR_SORTED;
	}

	tempArrayPtr = (int*) malloc (sizeof(int)*numOfElements);
	if (NULL == tempArrayPtr)
	{
		return ERR_NOT_INITIALIZED;
	}

	RecMergeArray(_vec ,tempArrayPtr , 0 ,numOfElements -1);
	free(tempArrayPtr);
	return ERR_OK;
}


/******************************************************************************/
/******************************************************************************/
static ADTErr FreqOfElements(Vector* _vec, size_t* _countArray, size_t _itemsNum,int _digitPlace )
{
	size_t  index;
	int value;
	int i;
	
	for (index=0 ; index < _itemsNum; index++)
	{
		VectorGet(_vec, index, &value);
		value = (value/_digitPlace)%10; 
		_countArray[value]++;
	}
}
/******************************************************************************/
static ADTErr Cumolate(size_t* _countArray, int _maxValue)
{
	int index ;

	for (index =1; index<_maxValue+1 ;index++)
	{
		_countArray[index] += _countArray[index-1];
	}
} 

/******************************************************************************/
static void CountSortingAction (Vector* _vec, size_t* _countArray,int* _sortedVectorPtr,size_t _itemsNum, int _digitPlace )
{
	int index;
	int value;
	size_t vectorIndex;
	
	vectorIndex=_itemsNum-1;
	for (index=_itemsNum-1 ; index>=0 ; index--)
	{		
		VectorGet(_vec, vectorIndex, &value);		
		_sortedVectorPtr[_countArray[(value/_digitPlace)%10]-1] = value;
		_countArray[(value/_digitPlace)%10]--;
		vectorIndex--;
	}
}
/******************************************************************************/
static void copyArray(Vector* _vec, int* _sortedVectorPtr, size_t _itemsNum)
{
	int value;
	size_t index;

	for (index=0; index<_itemsNum ;index++)
	{
		value = _sortedVectorPtr[index];
		VectorSet(_vec, index,value);
	}
}
/******************************************************************************/
ADTErr CountSort(Vector* _vec, int _maxValue, int _digitPlace )
{
	int index, i;	
	size_t itemsNum;
	int *sortedVectorPtr;
	size_t *countArrayPtr;

	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorItemsNum(_vec, &itemsNum);

	sortedVectorPtr = (int*) malloc (sizeof(int)*itemsNum);
	if (NULL == sortedVectorPtr)
	{
		return ERR_NOT_INITIALIZED;
	}

	countArrayPtr = (size_t*) calloc (_maxValue+1, sizeof(size_t));	
	if (NULL == countArrayPtr)
	{
		return ERR_NOT_INITIALIZED;
	}
		
	FreqOfElements(_vec,countArrayPtr,itemsNum, _digitPlace);
	Cumolate(countArrayPtr, _maxValue);
	CountSortingAction (_vec,countArrayPtr,sortedVectorPtr,itemsNum,_digitPlace);	
	copyArray(_vec, sortedVectorPtr,itemsNum);	
	free (sortedVectorPtr);		
}
/******************************************************************************/
void RadixSort(Vector* _vec, int _maxNumOfDigits)
{
	int digitPlace;
	int index;
	
	digitPlace=1;
	for (index=0; index<_maxNumOfDigits; index++)
	{
		CountSort(_vec ,NUM_OF_DIGITS , digitPlace);
		digitPlace*=10;
	}
	
}
/******************************************************************************/
int main (void)
{
	int i, randNum;
	clock_t t1, t2;
	Vector* vecPtr;
	int maxValue = 18;
	int maxNumOfDigits = 2;

	int array1[NUM_OF_ELEMENTS]= {0};
	int array2[NUM_OF_ELEMENTS]= {0};
	int array3[NUM_OF_ELEMENTS]= {0};
	int array4[NUM_OF_ELEMENTS]= {0};
	int array5[NUM_OF_ELEMENTS]= {0};
	int array6[NUM_OF_ELEMENTS]= {0};
	int array7[NUM_OF_ELEMENTS]= {0};
	int array8[NUM_OF_ELEMENTS]= {0};
	int array9[NUM_OF_ELEMENTS]= {0};
	
	int tempArray[12] = {6942,25,0,7852,2,14,456,2,480,10,32,18};
									/*2,1,3,1,2,2,0,0,0,1,*/

	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		array1[i] = rand() % NUM_OF_ELEMENTS;
		array2[i] = array1[i];
		array3[i] = array1[i];
		array4[i] = array1[i];
		array5[i] = array1[i];
		array6[i] = array1[i];
		array7[i] = array1[i];
		array8[i] = array1[i];
		array9[i] = array1[i];
		
	}
/*******************************************************/	
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array1[i]);
	}
	t1=clock();
	BubbleVector (vecPtr , NUM_OF_ELEMENTS);
	t2=clock();
	printf("BubbleVector Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);	
/*******************************************************/	

	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array2[i]);
	}
	t1=clock();
	ShakeVector(vecPtr);
	t2=clock();
	printf("ShakeVector Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array4[i]);
	}
	t1=clock();
	Insertion(vecPtr, NUM_OF_ELEMENTS);
	t2=clock();
	printf("Insertion Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array6[i]);
	}
	t1=clock();
	SelectionVector (vecPtr, NUM_OF_ELEMENTS);
	t2=clock();
	printf("Selection Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
/*******************************************************/

	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array5[i]);
	}
	t1=clock();
	ShellVector(vecPtr , NUM_OF_ELEMENTS);
	t2=clock();
	printf("Shell Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array7[i]);
	}
	t1=clock();
	MergSort(vecPtr);
	t2=clock();
	printf("Merge Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	/*VectorPrint(vecPtr);*/
/*******************************************************/	
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array3[i]);
	}
	t1=clock();
	Quick (vecPtr ,0 , NUM_OF_ELEMENTS-1);
	t2=clock();
	printf("Quick Sorting: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);

/*******************************************************/	
	/*vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array8[i]);
	}
	t1=clock();
	VectorPrint(vecPtr);
	CountSort(vecPtr , maxValue , digitPlace); 
	t2=clock();
	printf("CountSort: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	VectorPrint(vecPtr);

/*******************************************************/
	vecPtr = VectorCreate(NUM_OF_ELEMENTS, 500);
	for (i=0 ; i<NUM_OF_ELEMENTS; i++)
	{
		VectorAdd(vecPtr, array9[i]);
	}	
	t1=clock();
	RadixSort(vecPtr, maxNumOfDigits);
	t2=clock();
	printf("RadixSort: %f\n", (float)(t2-t1)/CLOCKS_PER_SEC);
	/*VectorPrint(vecPtr);*/
}
