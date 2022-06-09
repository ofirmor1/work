#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"
#include "User.h"
#include "Chat.h"
#define MAX_CHARS 10



#define FILE_NAME "UserData.txt"
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
  	char userName[MAX_CHARS];
  	char userPass[MAX_CHARS];
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

		memset(userName, 0, MAX_CHARS);
		memset(userPass, 0, MAX_CHARS);

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

/*FOR SERVER CREATE
if((LoadUserData(newManager -> m_users, FILE_NAME)) == FAIL)
{
	free(newManager);
	return NULL;
}
*/

/*FOR REGISTER
if((SaveUserData(FILE_NAME, _userName, _password)) == FAIL)
{
	return FAIL;
}
*/