#ifndef __DOUBLELINKEDLIST_H__
#define __DOUBLELINKEDLIST_H__
#include "ADTDefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node Node;
typedef struct List List;



List* ListCreate(void);

void ListDestroy(List* _list);

ADTErr ListPushHead(List* _list, int _data);

ADTErr ListPushTail(List* _list, int _data);

ADTErr ListPopHead(List* _list, int* _data);

ADTErr ListPopTail(List* _list, int* _data);

size_t ListCountItems(List* _list);

int ListIsEmpty(List* _list);

/* ListPrint is only for debug */

void ListPrint(List* _list);


#endif /*#ifndef __DOUBLELINKEDLIST_H__*/
