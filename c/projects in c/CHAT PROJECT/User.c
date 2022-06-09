#include <stdlib.h>
#include <stddef.h> 
#include <string.h>
#include "Iterator.h"
#include "User.h"
#include "Chat.h"
#define MAX_CHARS 10

void DestroyGroupName(void * _groupName);
/***********************************User Struct***************************************************/
struct User
{
	char   m_username[MAX_CHARS];
	char   m_password[MAX_CHARS];
	List * m_groups;
	int    m_active;
	int    m_clientID;
};


/***********************************User Create***************************************************/
User * CreateUser(char * _userName, char * _password)
{
	User * newUser = (User*)malloc(sizeof(User));
	if(newUser == NULL)
	{
		return NULL;
	}
	
	if((newUser -> m_groups = ListCreate()) == NULL)
	{
		free(newUser);
		return NULL;
	}
	
	strcpy(newUser -> m_username, _userName); 
	strcpy(newUser -> m_password, _password); 
	newUser -> m_active = NOT_ACTIVE;
	newUser -> m_clientID = EMPTY;

	return newUser;
}

/***********************************User Destroy**************************************************/
void DestroyUser(User ** _user)
{
	if(_user == NULL || *_user == NULL)
	{
		return;
	}
	ListDestroy(&((*_user) -> m_groups), DestroyGroupName);
	free(*_user);
	*_user = NULL;
}

void DestroyGroupName(void * _groupName)
{
	free((char*)_groupName);
}
/***********************************Add Group*****************************************************/
void AddGroup(User * _user, char * _group)
{
	char * groupName = (char*)malloc(strlen(_group)+1);
	strcpy(groupName, _group);
	ListPushTail(_user -> m_groups, (void*)groupName);
}
/***********************************Remove All Groups*********************************************/
void LeaveAllGroups(User * _user)
{
	ListItr curr = ListItrBegin(_user -> m_groups);
	ListItr end = ListItrEnd(_user -> m_groups);
	while(curr != end)
	{
		DestroyGroupName(ListItrGet(curr));
		ListItrRemove(curr);
		curr = ListItrNext(curr);
	}
}

/***********************************Remove Group**************************************************/
int LeaveOneGroup(User * _user, char * _group)
{
	ListItr curr, end;
	void * elem; 
	curr = ListItrBegin(_user -> m_groups);
	end = ListItrEnd(_user -> m_groups);
	while(curr != end)
	{
		elem = ListItrGet(curr);
		if(strcmp((char*)elem, _group) == 0)
		{
			free((char*)elem);
			ListItrRemove(curr);
			return SUCCESS;
		}
		curr = ListItrNext(curr);
	}
	return NOT_FOUND;
}

/***********************************Is In Group***************************************************/
int IsInGroup(User * _user, char * _group)
{
	ListItr curr, end;
	void * elem; 
	curr = ListItrBegin(_user -> m_groups);
	end = ListItrEnd(_user -> m_groups);
	while(curr != end)
	{
		elem = ListItrGet(curr);
		if(strcmp((char*)elem, _group) == 0)
		{
			return SUCCESS;
		}
		curr = ListItrNext(curr);
	}
	return NOT_FOUND;
}

/***********************************User Activate*************************************************/
void Activate(User * _user, int _clientID)
{
	_user -> m_active = ACTIVE;
	_user -> m_clientID = _clientID;
}

/***********************************User DeActivate***********************************************/
void DeActivate(User * _user)
{
	_user -> m_active = NOT_ACTIVE;
	_user -> m_clientID = EMPTY;
}

/***********************************User IsActive*************************************************/
int IsActive(User * _user)
{
	return _user -> m_active;
}

/***********************************User Get******************************************************/
char * GetPassword(User * _user)
{
	return _user -> m_password;
}

char * GetUserName(User * _user)
{
	return _user -> m_username;
}

int GetClientID(User * _user)
{
	return _user -> m_clientID;
}

List * GetUserGroupsList(User * _user)
{
	return _user -> m_groups;
}



