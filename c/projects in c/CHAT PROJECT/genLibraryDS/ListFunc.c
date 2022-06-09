#include "ListFunc.h"
#include <stdlib.h>


void* GenericLoop(ListItr _begin, ListItr _end, int (*func1)(void * _element, void* _context),
int (*func2)(int result, int *_param), int  *_counter, void *_context){
	int i;
	void* element;
	ListItr *current = _begin;
 	while(current != _end){
		element = ListItrGet(current);
		i = func1(element, _context);
		if(func2(i, _counter) == 0){
			break;
		}
		current = ListItrNext(current);
	}
	return (ListItr*)current;
}


int findFirstCondition(int result, int *_paramter){

	if(result == 1){
		return 0;
	}
	if(result == 0){
		return 1;
	}
}

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context){
	ListItr *toSend;
	toSend = GenericLoop(_begin,_end, _predicate, findFirstCondition, NULL, NULL);
	return toSend;
}


int CountCondition(int result, int *_counter){
	if(result == 1){
		(*_counter) = (*_counter) + 1;
	}
	return 1;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context){
	int *toSend;
	int i = 0;
	toSend = &i;
	GenericLoop(_begin,_end, _predicate, CountCondition, toSend, NULL);
	return *toSend;

}

int ForEachCondition(int result, int *_counter){
	if(result == 0){
		return 0;
	}
	return 1;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context){
	ListItr *toSend;
	toSend = GenericLoop(_begin,_end, _action, ForEachCondition, NULL, NULL);
	return toSend;
}

