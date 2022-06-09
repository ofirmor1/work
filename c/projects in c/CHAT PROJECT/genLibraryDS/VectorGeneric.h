#ifndef __VECTORGENERIC_H__
#define __VECTORGENERIC_H__
#include <stddef.h>  /* size_t */

typedef struct Vector Vector;
typedef int(*VectorElementAction)(void* _element, size_t _index, void* _context);

typedef enum Vector_Result {
	VECTOR_SUCCESS,
	VECTOR_UNITIALIZED_ERROR,/**< Uninitialized vector error 	*/
	VECTOR_ALLOCATION_ERROR,/**< realloc error on grow/shrink   */
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,
	VECTOR_OVERFLOW,
	VECTOR_UNDERFLOW
	/* Add more as needed by your implementation */
} VectorResult;

/*Description:This func creating new generic vector
Input:the initialsize and the blocksize to extend if necessery.
Output:pointer to the start of the vector.
error: if the allocation fail it returns null*/
Vector* VectorCreate (size_t _initialSize, size_t _extensionBblockSize);

/*Description:This func destroy the dynamicvector and the structs inside the vector if exist.
Input: pointer to the start of the vector.
Output: void
error: none*/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item));

/*Description:This func adding new element(generic) to the vector and incremet the vector if neseccry.
Input:pointer to the start of the vector and the item to insert.
Output:flag which tell us status -ok/error 
error: notinitialized/reallocationfault/overflow*/
VectorResult VectorAppend(Vector* _vector, void* _item);


/*Description:This func deleting the last element from the vector and discriminate if nesaccery
Input:pointer to the start of the vector and pointer for item to insert the deleting element.
Output:flag which tell us status 
error: notinitialized/reallocationfault/undeflow*/
VectorResult VectorRemove(Vector* _vector, void** _pValue);

/*Description:This func return an generic element ,specific value/ specific struct.
Input:pointer to the start of the vector, the specific index and pointer for item to insert the returning element.
Output:flag which tell us status 
error: if index is invalid-err_erong_index */
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue);


/*Description:This func change generic element ,specific value/ specific struct.
Input:pointer to the start of the vector, the specific index and pointer for item to insert the changing element.
Output:flag which tell us status 
error: if index is invalid */
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value);

/*Description:This func return the number of element in the array. 
Input:pointer to the start of the vector 
Output:number of elements
error: none */
size_t VectorSize(const Vector* _vector);

/*Description:This func return the capacity of the vector
Input:pointer to the start of the vector 
Output:the capacity size
error: none */
size_t VectorCapacity(const Vector* _vector);



size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context);


#endif /*__DynamicVector_h__*/
