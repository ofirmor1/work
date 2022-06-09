#include "ADTDefs.h"
#define MEGIC_NUMBER 12342

struct Stack

{
	Vector *m_vector;
	int m_magicNumber;
};


Stack* StackCreate (size_t _size, size_t _blockSize)
{
	
	Stack* ptrStack=NULL;

	if(_size==0 && _blockSize==0)
	{
		return NULL;
	}
	
	
	ptrStack=(*Stack)malloc(sizeof(Stack));
	if(ptrStack==0)
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

void StackDestroy(Stack* _stack);
{
	
	if(NULL==_stack || ptrStack->m_magicNumber!=MEGIC_NUMBER)
	{
		return;
	}
	ptrStack->m_magicNumber=0;
	VectorDestroy(ptrStack->m_vector);
	free (ptrStack);
	}
}

ADTErr StackPush (Stack* _stack, int _item);
{

}

ADTErr StackPop (Stack* _stack, int* _item);
{

}

ADTErr StackTop (Stack* _stack, int* _item);
{

}

int StackIsEmpty(Stack* _stack)
{

}

/* Unit-Test functions */

void StackPrint (Stack *_stack);
{

}
