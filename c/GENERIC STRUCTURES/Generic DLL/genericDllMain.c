#include <stdio.h>
#include "genericDll.h"

struct Node
{
int m_data;
Node* m_next;
Node* m_prev;
};

struct List
{
Node m_head;
Node m_tail;
};

void* ListDataReadByIndex(List *_list, int index)
{   
    Node *data;
    int j;
    size_t size = ListSize(_list);
    if(((size - index - 1) < 0) || (index < 0))
    {
        return NULL;
    }
    
    data = _list->m_head.m_next;
    for(j = 0; j < index; j++)
    {
        data = data->m_next;
    }

    return &(data->m_data);
}

int main()
{
    char *hello, *world;
    List *listPtr = ListCreate();
    ListPushHead(listPtr, "Hello");
    ListPushTail(listPtr, "World");
    hello = ListDataReadByIndex(listPtr, 0);
    world = ListDataReadByIndex(listPtr, 1);
    printf("%s %s\n", hello, world);
    ListDestroy((&listPtr), NULL);
    printf("\nSUCCESS\n");
    return 0;
}