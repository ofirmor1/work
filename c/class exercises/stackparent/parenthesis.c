#include "stack.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define NOT_BALANCED 0 
#define BALANCED 1 
#define NULL_ERROR -1

int IsParenthesOk(char _str[])
{
	Stack* ptrStack;	
	int length, i, item ,isEmpty;
	
	length = strlen(_str);
	
	ptrStack= StackCreate(length, 2);

	if( NULL==ptrStack)
		{
			return NULL_ERROR;
		}

	
	for(i=0; i<length ;i++)
	{
		if(_str[i]=='{' ||_str[i]=='[' ||_str[i]=='(' )
		{
			StackPush(ptrStack, (int)_str[i]);
		}
		else if(_str[i]=='}' ||_str[i]==']' ||_str[i]==')')
		{
			if (StackIsEmpty(ptrStack) == 1)
			{
				StackDestroy(ptrStack);
				return NOT_BALANCED;
			}
			else 
			{	
				StackPop(ptrStack, &item);
				if( !((item== '[' &&   _str[i]==']')
				  ||  (item== '(' &&   _str[i]==')')
				  ||  (item== '{' &&   _str[i]=='}')))
				{
					StackDestroy(ptrStack);
					return NOT_BALANCED;
				}
			}
		}		
	}
	isEmpty=StackIsEmpty(ptrStack);
	if(isEmpty == 0)
	{
		StackDestroy(ptrStack);
		return NOT_BALANCED;
	}
	else
	{
		StackDestroy(ptrStack);		
		return BALANCED;	
	}
		
}

int main (void)
{
	char str []="{}"; 
	int isParentOk;	
	
	isParentOk=IsParenthesOk(str);
	printf("%d \n",isParentOk);
		
}
