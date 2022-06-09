#ifndef __GROUP_H__
#define __GROUP_H__
#include <stddef.h> 

typedef struct Group Group;

/***********************************Group Create**************************************************/
Group * CreateGroup(char * _groupName, char * _groupIP);
/***********************************Group Destroy*************************************************/
void DestroyGroup(Group ** _group);
/***********************************Group Get*****************************************************/
char * GetGroupIP(Group * _group);
char * GetGroupName(Group * _group);
char * GetGroupPort(Group * _group);
int GetNumOfMembers(Group * _group);
/******************************Add/Less Memeber to Group count************************************/
/* Plus Member To Count
description: Add counter to the counter member Group numOfMembers. 
parameters: pointer to the Group.
return: num of members.
error-handling:
*/
int PlusMemberToCount(Group * _group);

/* Minus Member To Count
description: Lower counter to the counter member Group numOfMembers, if counter down to zero, them destroy the group.
parameters: pointer to the Group.
return: num of members.
error-handling:
*/
int MinusMemberFromCount(Group * _group);

#endif /*__GROUP_H__*/

