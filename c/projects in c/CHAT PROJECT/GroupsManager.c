#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "HashMap.h"
#include "UserManager.h"
#include "Group.h"
#include "GroupsManager.h"
#include "GenericDouble.h"
#include "GenericQueue.h"
#include "VectorGeneric.h"
#include "Iterator.h"
#include "IP.h"
#define HASH_SIZE 200


void GroupValDestroy(void* _group);
int printGroups(const void* _key, void* _value, void* _context);
/***********************************Group Manager Struct******************************************/
struct GroupsManager
{
    GroupIPs * m_IPs;
    HashMap *  m_groups;
    int        m_numOfGroups;
};

/***********************************Group Manager Create******************************************/
GroupsManager * CreateGroupsManager(HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    GroupsManager * newGM = (GroupsManager*)malloc(sizeof(GroupsManager));
    if(newGM == NULL)
    {
        return NULL;
    }

    newGM -> m_IPs = IPs_Create();
    if(newGM -> m_IPs == NULL)
    {
        return NULL;
    }

   newGM -> m_groups = HashMap_Create(HASH_SIZE, _hashFunc, _keysEqualFunc);
   if(newGM -> m_groups == NULL)
    {
        return NULL;
    }

    newGM -> m_numOfGroups = 0;

    return newGM;
}

/***********************************Groups Manager Destroy****************************************/
void DestroyGroupsManager(GroupsManager ** _groupsManager)
{
	if(_groupsManager == NULL || *_groupsManager == NULL)
	{
		return;
	}
	HashMap_Destroy(&((*_groupsManager) -> m_groups), NULL, GroupValDestroy); /*to check if its works*/
    IPs_Destroy((*_groupsManager) -> m_IPs);
	free(*_groupsManager);
	*_groupsManager == NULL;
}

/*****************destroy hashmap help********************/
void GroupValDestroy(void * _group)
{
	Group * temp = (Group*)_group;
	DestroyGroup(&temp);
}

/***************************************create Group *******************************************/
ReqStats CreateNewGroup(GroupsManager * _groupManager, char *_groupName, char *IP)
{
	char* tmp;
	Group *currGRoup;
	Group *pValue;
	int status;
	if((HashMap_Find(_groupManager -> m_groups, (void*)_groupName, (void*)(&pValue))) == MAP_SUCCESS)
	{
		return CREATE_GROUP_ERR;
	}
	IPs_RemoveIP(_groupManager->m_IPs, IP);
	currGRoup = CreateGroup(_groupName, IP);
	tmp = (char*)malloc(strlen(_groupName)+1);
	if(tmp == NULL)
	{
		return CREATE_GROUP_ERR;
	}	
	strcpy(tmp, _groupName);
	status = HashMap_Insert(_groupManager -> m_groups, (void*)tmp, (void*)currGRoup);
	if(status != MAP_SUCCESS)
	{
		return CREATE_GROUP_ERR;
	}
 	(_groupManager -> m_numOfGroups)++;
	return CREATE_GROUP_SUCCESS;
}

/***********************************get GroupIP***************************************************/
ReqStats getGroupIP(GroupsManager * _groupManager, char *_groupName, char *IP)
{
	Group *pValue;
	if((HashMap_Find(_groupManager -> m_groups, (void*)_groupName, (void*)(&pValue))) != MAP_SUCCESS)
	{
		return NOT_FOUND;
	}

    strcpy(IP, GetGroupIP(pValue));
	return FOUND;
}

/******************************Get Port By Group Name*********************************************/
char* GetPortByGroupName(GroupsManager * _groupsManager, char *_groupName)
{
	Group *pValue;
	HashMap_Find(_groupsManager -> m_groups, (void*)_groupName, (void*)(&pValue));
	return GetGroupPort(pValue);
}

/******************************Add/Less Memeber to Group count************************************/
void AddCountGroupNumOfMember(GroupsManager * _groupManager, char *_groupName)
{
	Group *currGroup;
	HashMap_Find(_groupManager -> m_groups, (void*)_groupName, (void*)(&currGroup));
	PlusMemberToCount(currGroup);
}

void LessCountGroupNumOfMember(GroupsManager * _groupsManager, char *_groupName)
{
	Group *currGroup;
	char IP[15];
	HashMap_Find(_groupsManager -> m_groups, (void*)_groupName, (void*)(&currGroup));
	getGroupIP(_groupsManager, _groupName, IP);
	if(MinusMemberFromCount(currGroup) == 0)
	{
		IPs_InsertIP(_groupsManager->m_IPs, IP);
		(_groupsManager -> m_numOfGroups) -= 1;
	}
}

/******************************Get Group List*****************************************************/
void GetGroupsList(GroupsManager * _groupManager, Vector *_GroupsName){

	HashMap_ForEach(_groupManager -> m_groups, printGroups, (void*)_GroupsName);
}

/******************************Print Groups*****************************************************/
int printGroups(const void* _key, void* _value, void* _context){
	char *tmp = (char*) malloc(sizeof(char)*strlen((char*)_key));
	strcpy(tmp,(char*)_key);
	VectorAppend((Vector*)_context, (void*)tmp);
	return 1;
}

void GroupUserLogOut(GroupsManager * _groupManager, List * _userGroups)
{
	char * groupName;
	ListItr curr = ListItrBegin(_userGroups);
	ListItr end = ListItrEnd(_userGroups);
	while(curr != end)
	{
		groupName = (char*)ListItrGet(curr);
		LessCountGroupNumOfMember(_groupManager, groupName);
		curr = ListItrNext(curr);
	}	
}