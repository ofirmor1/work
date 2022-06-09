#ifndef __INTERNALLISTITR_H__
#define ____INTERNALLISTITR_H___H__
#include <stdlib.h>

struct Node{

void* m_data;
Node* m_next;
Node* m_prev;

};

struct List{

Node m_head;
Node m_tail;

};

Node* NodeCreate(void *_data);

#endif
