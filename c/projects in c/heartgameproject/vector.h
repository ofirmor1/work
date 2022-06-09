#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ADTDefs.h"


typedef struct Vector Vector;

Vector* VectorCreate(size_t _initialSize, size_t _extentionBblockSize);
void VectorDestroy(Vector* _vector);
ADTErr VectorAdd(Vector* _vector, int _item);
ADTErr VectorDelete (Vector* _vector, int* _item);
ADTErr VectorGet(Vector *_vector, size_t _index, int* _item);
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);
ADTErr VectorItemsNum(Vector* _vector, size_t* _numOfItems);
void VectorPrint(Vector *_vector);





#endif /*#ifndef __VECTOR_H__*/
