#ifndef __LIST_STRUCTS_H__
#define __LIST_STRUCTS_H__


typedef struct Node Node;

typedef enum List_Result{
	LIST_SUCCESS = 0,
	LIST_UNINITIALIZED_ERROR,
	LIST_ALLOCATION_ERROR,
	LIST_NULL_ELEMENT_ERROR,
	LIST_UNDERFLOW_ERROR,
	LIST_IS_EMEPTY_ERROR,
	LIST_IS_NOT_EMEPTY_ERROR
}List_Result;

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	int m_magicNumber;
};

#endif
