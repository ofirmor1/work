#include <

Typedef struct Stack 
{
	Vector *m_vector;
	int m_magicNumber;
}Stack;

Stack* StackCreate (size_t _size, size_t _blockSize)
{
	Stack* ptrStack = NULL;
	if(_size==0 && _blockSize==0)
	{
		return NULL;
	}
	Stack *ptrStack = (stack*)malloc(sizeof(stack)); 
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
void StackDestroy(Stack* _stack)
{
	if(_stack == NULL || _stack -> magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	ptrStack->m_magicNumber=0;
	VectorDestroy(ptrStack->m_vector);
	free (ptrStack);	
}
ADTErr StackPush (Stack* _stack, int _item);
ADTErr StackPop (Stack* _stack, int* _item);
{
..
}
ADTErr StackTop (Stack* _stack, int* _item)
{
	    if (!isEmpty(ptr)) {
        return ptr->items[ptr->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
int StackIsEmpty(Stack* _stack)
{
	return ptr->top == -1;
}

int main(void)
{
	//
}
