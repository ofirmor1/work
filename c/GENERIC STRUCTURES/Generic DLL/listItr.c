#include "listStructs.h"
#include "genericDll.h"
#include "listItr.h"
#include <stdlib.h>

/*****************************************************/
ListItr ListItrBegin(const List* _list)
{
	if(NULL == _list)
    {
        return NULL;
    }
    
    return (ListItr)_list->m_head.m_next;
}
/*****************************************************/
ListItr ListItrEnd(const List* _list)
{
if(NULL == _list)
    {
        return NULL;
    }
    
    return (ListItr)&_list->m_tail;
}
/*****************************************************/
int ListItrEquals(const ListItr _a, const ListItr _b)
{
	return _a == _b;
}
/*****************************************************/
ListItr ListItrNext(ListItr _itr)
{
    if(NULL == _itr)
    {
        return NULL;
    }
    if(((Node*)_itr)->m_next != NULL)
    {
        return (ListItr)(((Node*)_itr)->m_next);
    }

    return _itr;

}
/*****************************************************/
ListItr ListItrPrev(ListItr _itr)
{
    if(NULL == _itr)
    {
        return NULL;
    }
    if(((Node*)_itr)->m_prev->m_prev != NULL)
    {
        return (ListItr)(((Node*)_itr)->m_prev);
    }

    return _itr;
}
/*****************************************************/
void* ListItrGet(ListItr _itr)
{
    if(NULL == _itr || NULL == ((Node*)_itr)->m_next)
    {
        return NULL;
    }

    return (((Node*)_itr)->m_data);
}
/*****************************************************/
void* ListItrSet(ListItr _itr, void* _element)
{
    void* item = NULL;
    if(NULL == _itr || NULL == _element || NULL == ((Node*)_itr)->m_next)
    {
        return NULL;
    }
    item = ((Node*)_itr)->m_data;
    ((Node*)_itr)->m_data = _element;

    return item;
}
/*****************************************************/
ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	if(NULL == _itr)
	{
		return NULL;
	}
	if(InsertBefore((Node*)_itr, _element) != LIST_SUCCESS)
	{
		return NULL;
	}

	return ListItrPrev(_itr);
}
/*****************************************************/
void* ListItr_Remove(ListItr _itr)
{
	void* data;
	if(NULL == _itr || NULL == (((Node*)_itr))->m_next)
	{
		return NULL;
	}
	Remove((Node*)_itr, &data);

	return data;
}
