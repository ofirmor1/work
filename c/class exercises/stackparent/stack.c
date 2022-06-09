#include <stdlib.h>
#include "ADTDefs.h"
#include <stddef.h>
#include "Vector.h"
#include "stack.h"
#define MEGIC_NUMBER 12342


struct Stack 
{
	Vector *m_vector;
	int m_magicNumber;
};


Stack* StackCreate (size_t _size, size_t _blockSize)
{
	
	Stack* ptrStack;

	if(_size==0 && _blockSize==0)
	{
		return NULL;
	}
	
	
	ptrStack=(Stack*)malloc(sizeof(Stack));
	if(ptrStack==NULL)
	{
		return NULL;
	}

	ptrStack->m_vector=VectorCreate(_size,_blockSize);

	if (NULL==ptrStack->m_vector)
	{
		free(ptrStack);
		return NULL;
	}
	
	ptrStack->m_magicNumber=MEGIC_NUMBER;
}
/**********************Destroy*******************************/
void StackDestroy(Stack* _stack)
{
	
	if(NULL==_stack || _stack->m_magicNumber!=MEGIC_NUMBER)
	{
		return;
	}
	_stack->m_magicNumber=0;
	VectorDestroy(_stack->m_vector);
	free (_stack);
	
}
/**********************push*********************************/

ADTErr StackPush (Stack* _stack, int _item)
{
		if (NULL==_stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return VectorAdd(_stack->m_vector, _item);
		
}


/*************************Pop*******************************/
ADTErr StackPop (Stack* _stack, int* _item)
{
	if (NULL==_stack||NULL==_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return VectorDelete(_stack->m_vector, _item);

}
/*************************Top*******************************/
ADTErr StackTop (Stack* _stack, int* _item)
{
	size_t numOfItems;
	if (NULL==_stack||NULL==_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_stack->m_vector, &numOfItems);
	
	return VectorGet(_stack->m_vector, numOfItems-1, _item);
	
}
/*******************StackIsEmpty******************************/
int StackIsEmpty(Stack* _stack)
{
	size_t numOfItems;
	
	if (NULL==_stack)
	{
		return STACK_IS_EMPTY;
	}

	VectorItemsNum(_stack->m_vector, &numOfItems);	
	if(numOfItems==0)
	{
		return STACK_IS_EMPTY;
	}
	return STACK_IS_NOT_EMPTY;
}
/*******************Print******************************/
/* Unit-Test functions */

void StackPrint (Stack *_stack)
{
	if (NULL==_stack)
	{
		return;
	}
	
	VectorPrint(_stack->m_vector);
	
}
/**************************************************************/
/*******************NumOfElements******************************/
size_t GetNumberOfElements(Stack* _stack )
{
	size_t numberOfElements;
	VectorItemsNum(_stack->m_vector, &numberOfElements);	
	return numberOfElements;
}




