#include "list_functions.h"
#include "listItr.h"
#include <stdlib.h>

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr current = _begin;
	if(NULL == _predicate) 
	{
		return _end;
	}
	while(current != NULL && current != _end && ListItrNext(current) != NULL)
	{
		if( (*
		_predicate)( ListItrGet(current), _context) )
		{
			return (ListItr)current;
		}
		current = ListItrNext(current);
	}
	return (ListItr)current;
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t count = 0;
	ListItr current = _begin; 
	if(!_predicate)
	{
		return count;
	}
	while( current != NULL && current != _end && ListItrNext(current) != NULL)
	{
		if( (*_predicate)( ListItrGet(current), _context) )
		{
			++count;
		}
		current = ListItrNext(current);
	}
	return count;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	ListItr current = _begin;
	if(!_action)
	{
		return _end;
	}
	while( current != NULL && current != _end && ListItrNext(current) != NULL)
	{
		if( !(*_action)( ListItrGet(current), _context) )
		{
			return (ListItr)current;
		}
		current = ListItrNext(current);
	}
	return (ListItr)current;
}

