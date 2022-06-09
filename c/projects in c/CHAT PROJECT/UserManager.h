#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__
#include <stddef.h> 
#include "HashMap.h"
#include "Chat.h"
#include "GenericDouble.h"

#define NOT_ACTIVE 0 
#define ACTIVE 1

typedef struct UsersManager UsersManager;

/***********************************User Manager Create*******************************************/
/* Create User Manager
description: Allocate new User Manager and create new hashmap with the the two pointer to func from the parameters.
parameters: int max users (hashmap size), pointer to hash function, pointer to keys equal function.
return: pointer to the User Manager.
error-handling: NULL if one of the allocations fail.
*/
UsersManager * CreateUsersManager(int _maxUsers, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
/***********************************User Manager Destroy******************************************/
/* Destroy User Manager
description: Destroy hashmap, free the memory of hashmap and memory of the struct and change struct pointer to NULL. 
parameters: pointer to UserManger pointer.
return: 
error-handling: non if on the pinters in the parameters holds NULL.
*/
void DestroyUsersManager(UsersManager ** _usersManager);
/***********************************Register User*************************************************/
/* User registaration
description: Check if username not taken, create new user and insert it to the hashmap. 
parameters: pointer to User Manager, char pointer to user name and char pointer to password.
return: status REG_SUCCESS if user created or USER_EXIST if user name token
error-handling: REG_ERR if crate user fail or insert fail.
*/
ReqStats Register(UsersManager * _usersManager, char * _userName, char * _password);
/***********************************Login User****************************************************/
/* User LogIn
description: check if username exist then check if password input match the password of the user, if yes, activating the user.
parameters: pointer to User Manager, char pointer to user name, char pointer to password and int clientID.
return: LOGIN_SUCCESS if log in succeed
error-handling: LOGIN_ERR if log in failed.
*/
ReqStats UserLogIn(UsersManager * _usersManager, char * _userName, char * _password, int _clientID);
/***********************************LogOut User***************************************************/
/* User LogOut
description: Remove all the groups from user group list, and deactivating user.
parameters: pointer to User Manager and int clientID.
return: LOG_OUT_SUCCESS
error-handling:
*/
ReqStats UserLogOut(UsersManager * _usersManager, int * _clientID);

/***********************************User In Group*************************************************/
int IsUserInGroup(UsersManager * _userManager, char * _userName, char * _groupName);
/***********************************User Join Group***********************************************/
ReqStats UserJoinGroup(UsersManager * _userManager, char * _userName, char * _groupName);
/***********************************User Leave One Group******************************************/
ReqStats LeaveTheGroup(UsersManager * _userManager, char * _userName, char * _groupName);
/***********************************User Leave All Group******************************************/
void ExitGroups(UsersManager * _userManager, char * _userName);

List * GetGroupsListByUserName(UsersManager * _userManager, char * _userName);



#endif /*__USERMANAGER_H__*/



