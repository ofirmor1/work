#ifndef __SORTALGORITHEM_H__
#define __SORTALGORITHEM_H__
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "ADTDefs.h"



ADTErr BubbleVector (Vector* _vec , size_t _numOfElements);

ADTErr ShakeVector (Vector* _vec);

ADTErr QuickSort (Vector* _vec , size_t _startIndex , size_t _endIndex);

ADTErr Insertion(Vector* _vec, size_t _numOfElements);

ADTErr ShellVector(Vector* _vec , size_t _numOfElements);

ADTErr SelectionVector (Vector* _vec, size_t _numOfElements);

ADTErr MergSort(Vector* _vec);

void RadixSort(Vector* _vec, int _maxNumOfDigits);


#endif /*#ifndef __SORTALGORITHEM_H__*/
