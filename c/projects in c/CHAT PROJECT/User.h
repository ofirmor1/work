#ifndef __USER_H__
#define __USER_H__
#include <stddef.h> 
#include "Iterator.h"
#define NOT_ACTIVE 0 
#define ACTIVE 1
#define EMPTY -1



typedef struct User User;

/***********************************User Create***************************************************/
/* Create new user
description: Allocate new user and list member, save the username and password into the members and intilize the clientID member to EMPTY.
parameters: char pointer to user name and char pointer to password.
return: pointer to the new user.
error-handling: NULL if one of the allocations fail.
*/
User * CreateUser(char * _userName, char * _password);
/***********************************User Destroy**************************************************/
/* destroy user
description: destroy the list and then free the list member then free the user.
parameters: pointer to user address.
return:
error-handling:
*/
void DestroyUser(User ** _user);
/***********************************Add Group*****************************************************/
/* Add group
description: add new group to the list int the user member. 
parameters: pointer to the user, pionter to the group.
return: return status of listpush func;
error-handling: 
*/
void AddGroup(User * _user, char * _group);
/***********************************Leave Groups**************************************************/
/* Leave group
description: Remove all Groups from the list. 
parameters: pointer to the user.
return: 
error-handling: 
*/
void LeaveAllGroups(User * _user);
/***********************************Remove Group**************************************************/
/* Remove group
description: remove group from the list.
parameters: pointer to the user, pionter to the group.
return: SUCCESS
error-handling: NOT_FOUND if user not in the group.
*/
int LeaveOneGroup(User * _user, char * _group);
/***********************************Is In Group***************************************************/
/* Is in group
description: Check if user in group or not 
parameters: pointer to the user, pionter to the group.
return: SUCCESS if yes and NOT_FOUND if not.
error-handling: 
*/
int IsInGroup(User * _user, char * _group);
/***********************************User Activate*************************************************/
/* Activate
description: change the active member to ACTIVE and save the clientID in the user struct.
parameters: pointer to user and int clientID.
return: 
error-handling: 
*/
void Activate(User * _user, int _clientID);
/***********************************User DeActivate***********************************************/
/* De Activate
description: change the active member to NOT_ACTIVE and the clientID member to EMPTY.
parameters: pointer to user.
return: void
error-handling: 
*/
void DeActivate(User * _user);
/***********************************User IsActivate***********************************************/
/* Activate
description: check the active member of the user.
parameters: pointer to user.
return: ACTIVE if active or NOT_ACTIVE if not.
error-handling: 
*/
void IsActivate(User * _user);

char * GetPassword(User * _user);
char * GetUserName(User * _user);
int GetClientID(User * _user);
List * GetUserGroupsList(User * _user);


#endif /*__USER_H__*/



