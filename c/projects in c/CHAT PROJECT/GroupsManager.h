#ifndef __GROUPSMANAGER_H__
#define __GROUPSMANAGER_H__
#include <stddef.h> 
#include "HashMap.h"
#include "VectorGeneric.h"
#include "GenericDouble.h"
#include "Chat.h"

typedef struct GroupsManager GroupsManager;

/***********************************group Manager Create*******************************************/

GroupsManager * CreateGroupsManager(HashFunction _hashFunc, EqualityFunction _keysEqualFunc);

void DestroyGroupsManager(GroupsManager ** _groupsManager);

ReqStats getGroupIP(GroupsManager * _groupManager, char *_groupName, char IP[]);

ReqStats CreateNewGroup(GroupsManager * _groupManager, char *_groupName, char IP[]);

char* GetPortByGroupName(GroupsManager * _groupManager, char *_groupName);
/******************************Add/Less Memeber to Group count************************************/
void AddCountGroupNumOfMember(GroupsManager * _groupManager, char *_groupName);
void LessCountGroupNumOfMember(GroupsManager * _groupManager, char *_groupName);
void GetGroupsList(GroupsManager * _groupManager, Vector *_GroupsName);
void GroupUserLogOut(GroupsManager * _groupManager, List * _userGroups);

#endif /*__GROUPSMANAGER_H__*/


