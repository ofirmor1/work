#include "vectorTesting.h"
#include <stdio.h>
/***********************************************************/
Vector *vector1, *vector2, *vector3, *vector4, *vectorInt;
void VectorCreate()
{
    printf("~~~~~~~~~~~~~~~~  CREATE TEST  ~~~~~~~~~~~~~~~~~~~~~~\n");
    vector1 = VectorCreate(5, 1);
    vector2 = VectorCreate(8,1);
    vector3 = VectorCreate(2, 1);
    vector4 = VectorCreate(0,1);
    /* Vector *vector5 = vectorCreate(-1); */

    vectorPrint(vector1);
    vectorPrint(vector4);
    /* vectorPrint(vector5); */

    vectorDestroy(&vector2);
    vectorDestroy(&vector4);

    vectorInt = vectorCreate(3);
}
/***********************************************************/
void VectorAppend()
{
    printf(">>>>>>>>>>>>>  VectorAppend TEST  <<<<<<<<<<<<<\n");
    VectorAppend(vectorInt, 1);

    VectorAppend(vector1,"Hi");
    VectorAppend(vector1,"How");
    VectorAppend(vector3,"Are");
    VectorAppend(vector1,"You");

    printf("-----vector1-----\n");
    VectorPrint(vector1);
    printf("-----vector3-----\n");
    VectorPrint(vector3);
    printf("-----vector3 when over capacity-----\n");
    VectorAppend(vector3, "Hello");
    VectorAppend(vector3,"World");
    VectorPrint(vector3);
}
/***********************************************************/
void VectorDestroy()
{
    printf(">>>>>>>>>>>>>  VectorDestroy TEST  <<<<<<<<<<<<<\n");
    void *info;
    void **res = &info;
    printf("-----Print before pop-----\n");
    VectorPrint(vector1);
    /* VectorRemove (vector1, (int *) &res); why can i only do this way?? */
    VectorRemove(vector1, res);
    printf("-----Print after pop-----\n");
    VectorPrint(vector1);
    /*printf("%d", *res); */
}
/***********************************************************/
void VectorRemove()
{
    printf(">>>>>>>>>>>>>  REMOVE ELEMENT TEST  <<<<<<<<<<<<<\n");
    void *info;
    void **res = &info;

    printf("-----Print before remove-----\n");
    VectorPrint(vector1);

    printf("-----Print after remove-----\n");
    VectorRemove(vector1, res);
    VectorPrint(vector1);

    VectorRemove(vector1, res);
    VectorPrint(vector1);

}
/***********************************************************/
void VectorGet()
{
    printf(">>>>>>>>>>>>>  GET ELEMENT TEST  <<<<<<<<<<<<<\n");
    void *info;
    void **res = &info;
    VectorGet(vector3, 12, res);
}
/***********************************************************/
void VectorSetAnElement()
{
    printf(">>>>>>>>>>>>>  SET ELEMENT TEST  <<<<<<<<<<<<<\n");
    int info = 3;
    void *res = &info;
    VectorSet(vector3, 12, res);
}
/***********************************************************/
int FindMaxInt(const void * _element, size_t _index, void* _context)
{
	if(_index == 0 || (*((int*)_context) < *((int*)_element)))
	{
		*((int*)_context) = *((int*)_element);
	}
	/*if(*((int*)_context) < *((int*)_element)
	{
		*((int*)_context) = *((int*)_element);
	}*/

	return 1;
}
void Test()
{
    VectorCreate();
    VectorAppend();
    VectorDestroy();
    VectorRemove();
    VectorGet();
    VectorSet();
}
