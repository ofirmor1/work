#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "HashMap.h"
#include "User.h"
#include "UserManager.h"
#include "Chat.h"
#include <string.h>
#define CHAR_NUM 15
#define FILE_NAME "UserData.txt"


size_t HashFunctionByUsername(const void* _data);
int EqualityFunctionByUsername(const void* _currKey, const void* _searchKey);
void UserValDestroy(void* _user);
int LogOutByClientID(const void* _key, void* _value, void* _context);
int printValueKeyFunction(const void* _key, void* _value, void* _context);
static int SaveUserData(char* _fileName, char* _userName, char* _userPassword);
static int LoadUserData(HashMap* _hash, char* _fileName);
static User * GetUserByName(UsersManager * _userManager, char * _userName);
/***********************************User Manager Struct*******************************************/
struct UsersManager
{
	HashMap * m_users;
};

/***********************************User Manager Create*******************************************/
UsersManager * CreateUsersManager(int _maxUsers, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	UsersManager * newManager = (UsersManager*)malloc(sizeof(UsersManager));
	if(newManager == NULL)
	{
		return NULL;
	}
	
	newManager -> m_users = HashMap_Create(_maxUsers, _hashFunc, _keysEqualFunc);
	if(newManager -> m_users == NULL)
	{
		free(newManager);
		return NULL;
	}
	/*
	if((LoadUserData(newManager -> m_users, FILE_NAME)) == FAIL)
	{
		free(newManager);
		return NULL;
	}
	*/
	return newManager;
}

/***********************************User Manager Destroy******************************************/
void DestroyUsersManager(UsersManager ** _usersManager)
{
	if(_usersManager == NULL || *_usersManager == NULL)
	{
		return;
	}
	HashMap_Destroy(&((*_usersManager) -> m_users), NULL, UserValDestroy); /*to check if its works*/
	free(*_usersManager);
	*_usersManager == NULL;
}

/*****************destroy hashmap help********************/
void UserValDestroy(void* _user)
{
	User * temp = (User*)_user;
	DestroyUser(&temp);
}

/***********************************Register User*************************************************/
ReqStats Register(UsersManager * _usersManager, char * _userName, char * _password)
{
	Map_Result status;
	char *tmp;
	User * newUser;
	void * pValue;
	
	status = HashMap_Find(_usersManager -> m_users, (void*)_userName, &pValue);
	if(status == MAP_SUCCESS)	
	{
		return REG_ERR;
	}
	
	newUser = CreateUser(_userName, _password);
	if(newUser == NULL)
	{
		return REG_ERR;
	}
	tmp = (char*)malloc(strlen(_userName)+1);
	if(tmp == NULL){
		return REG_ERR;
	}
	strcpy(tmp, _userName);
	status = HashMap_Insert(_usersManager -> m_users, tmp, (void*)newUser);
	if(status != MAP_SUCCESS)
	{
		return REG_ERR;
	}
	/*
	if((SaveUserData(FILE_NAME, _userName, _password)) == FAIL)
	{
		return REG_ERR;
	}
	*/
	HashMap_ForEach(_usersManager -> m_users, printValueKeyFunction, NULL);
	return REG_SUCCESS;
}

/***********************************Login User****************************************************/
ReqStats UserLogIn(UsersManager * _usersManager, char * _userName, char * _password, int _clientID)
{
	Map_Result status;
	User * pValue;
	int checkPassword;
	char * toCheck;
	
	status = HashMap_Find(_usersManager -> m_users, (void*)_userName, (void*)(&pValue));
	if(status != MAP_SUCCESS)
	{
		return LOGIN_ERR;
	}
	toCheck = GetPassword(pValue);
	if((checkPassword = strcmp(toCheck, _password)) != 0)
	{
		return LOGIN_ERR;
	}
	Activate(pValue, _clientID);
	return LOGIN_SUCCESS;
}

/***********************************LogOut User***************************************************/
ReqStats UserLogOut(UsersManager * _usersManager, int * _clientID)
{
	HashMap_ForEach(_usersManager -> m_users, LogOutByClientID, (void*)_clientID);
	return LOG_OUT_SUCCESS;
}

int LogOutByClientID(const void* _key, void* _value, void* _context)
{
	if(GetClientID((User*)_value) == *(int*)_context)
	{
		DeActivate((User*)_value);
		LeaveAllGroups((User*)_value);
		return 0;
	}
	return 1;
}

/***********************************User In Group*************************************************/
int IsUserInGroup(UsersManager * _userManager, char * _userName, char * _groupName)
{
	User * currUser = GetUserByName(_userManager, _userName);
	if(IsInGroup(currUser, _groupName) == SUCCESS)
	{
		return SUCCESS;
	}
	return NOT_FOUND;
}

/***********************************User Join Group***********************************************/
ReqStats UserJoinGroup(UsersManager * _userManager, char * _userName, char * _groupName)
{
	User * currUser = GetUserByName(_userManager, _userName);
	if(IsInGroup(currUser, _groupName) == SUCCESS)
	{
		return JOIN_GROUP_ERR_ALREADY_IN;
	}
	AddGroup(currUser, _groupName);
	return JOIN_GROUP_SUCCESS;
}

/***********************************User Leave One Group******************************************/
ReqStats LeaveTheGroup(UsersManager * _userManager, char * _userName, char * _groupName)
{
	User * currUser = GetUserByName(_userManager, _userName);
	if(LeaveOneGroup(currUser, _groupName) == NOT_FOUND)
	{
		return LEAVE_GROUP_ERR;
	}
	return LEAVE_GROUP_SUCCESS;
}

/***********************************User Leave All Group******************************************/
void ExitGroups(UsersManager * _userManager, char * _userName)
{
	User * currUser = GetUserByName(_userManager, _userName);
	LeaveAllGroups(currUser);
}

/*************************Help Save And Load User Data***********************/
static int SaveUserData(char* _fileName, char* _userName, char* _userPassword)
{
	FILE *ptr;
	if(_fileName == NULL || _userName == NULL || _userPassword == NULL)
	{
		return FAIL;	
	}
	if((ptr = fopen(_fileName, "a+")) == NULL)
	{
		return FAIL;
	}
	fprintf(ptr, "%s %s\n", _userName, _userPassword);
	fclose(ptr);
	return SUCCESS; 
}


static int LoadUserData(HashMap* _hash, char* _fileName)
{
  	FILE * ptr;
  	User * newUser;
	Map_Result status;
  	char userName[CHAR_NUM];
  	char userPass[CHAR_NUM];
	char * tempN;
	char * tempP;
  	if(_hash == NULL || _fileName == NULL)
	{
		return FAIL;
	}
	ptr = fopen(_fileName, "r");
	if(ptr == NULL)
	{
		return FAIL;
	}
	
	fscanf(ptr, "%s", userName);
	fscanf(ptr, "%s", userPass);
	tempN = (char*)malloc(strlen(userName)+1);
	tempP = (char*)malloc(strlen(userPass)+1);
	strcpy(tempN, userName);
	strcpy(tempP, userPass);

	if((newUser = CreateUser(tempN, tempP)) == NULL)
	{
		fclose(ptr);
		free(tempN);
		free(tempP);
		return FAIL;
	}

	while(!feof(ptr))
	{
		status = HashMap_Insert(_hash, (void*)tempN, (void*)newUser);
		if(status != MAP_SUCCESS)
		{
			fclose(ptr);
			free(tempN);
			free(tempP);
			return FAIL;
		}

		memset(userName, 0, CHAR_NUM);
		memset(userPass, 0, CHAR_NUM);

		fscanf(ptr, "%s", userName);
		fscanf(ptr, "%s", userPass);
		tempN = (char*)malloc(strlen(userName)+1);
		tempP = (char*)malloc(strlen(userPass)+1);
		strcpy(tempN, userName);
		strcpy(tempP, userPass);

		if((newUser = CreateUser(tempN, tempP)) == NULL)
		{
			fclose(ptr);
			free(tempN);
			free(tempP);
			return FAIL;
		}
	}
	fclose(ptr);
	free(tempN);
	free(tempP);
	return SUCCESS;
}


/*************************Help Get User By UserName**************************/
static User * GetUserByName(UsersManager * _userManager, char * _userName)
{
	User * pValue;
	HashMap_Find(_userManager -> m_users, (void*)_userName, (void*)(&pValue));
	return pValue;
}

/**************** Help Print Users*******************************************/
int printValueKeyFunction(const void* _key, void* _value, void* _context){
	User* myUser = (User*)_value;
	printf("%s - ", (char*)_key);
	printf("%s", GetUserName(_value));
	printf("%s", GetPassword(_value));
	printf("\n\n\n");
	return 1; 
}

List * GetGroupsListByUserName(UsersManager * _userManager, char * _userName)
{
	User * pValue;
	HashMap_Find(_userManager -> m_users, (void*)_userName, (void*)(&pValue));
	return GetUserGroupsList(pValue);
}



