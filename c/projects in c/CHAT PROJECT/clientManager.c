#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "clientUI.h"
#include "Protocols.h"
#include "GenericDouble.h"
#include "VectorGeneric.h"
#include "genLibraryDS/Iterator.h"
#include "clientNet.h"
#include "Chat.h"

#define IP "127.0.0.1"
#define PORT 2000
#define USERNAME_LEN 10
#define PASSWORD_LEN 10
#define GROUP_NAME_LEN 20
#define IP_LEN 20
#define BUFFER_LEN 50

typedef struct Groupids Groupids;
/******************************************************************************************/
static void ClientManager_Run();
static int ClientManager_Login(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN], int* _logstatus, List** _userGroups, int counter);
static int ClientManager_Register(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN], int* _logstatus, List** _userGroups);
static void ClientManager_LogOut(int _serverSock, char _username[USERNAME_LEN], int* _logstatus, List** _userGroups);
static void ClientManager_MainMenu(int _serverSock, char _username[USERNAME_LEN], UserChoise choice, int *logStatus, List** userGroups);
static void ClientManager_GroupsMenu(int _serverSock, char _username[USERNAME_LEN], UserChoise choice, int *logStatus, List** userGroups);
static void ClientManager_JoinGroup(int _serverSock, char _username[USERNAME_LEN], List** _userGroups);
static void ClientManager_ShowGroups(int _serverSock, char* _username);
static void ClientManager_LeaveGroup(int _serverSock, List** userGroups, char _username[USERNAME_LEN]);
static void ClientManager_CreateGroup(int _erverSock, char _username[USERNAME_LEN], List** _userGroups);
static int createGroup(char* _buffer, char* _groupName, char* _username, int _serverSock, List** userGroups);
/********************************************************/

struct Groupids
{
	char* m_groupName;
	int m_pidClient;
	int m_pidServer;
};


/******************************************************************************************/
int main()
{
	ClientManager_Run();
}
/******************************************************************************************/
static void ClientManager_Run()
{
    int serverSock, logStatus = 0;
    char username[USERNAME_LEN];
    UserChoise choice;
    List** userGroups;
    serverSock = ClientInit(IP, PORT);
    choice = ClientUI_HomePage();
    ClientManager_MainMenu(serverSock, username, choice, &logStatus, userGroups);
    /*ClientManager_LogOut(serverSock, username, &logStatus, userGroups);*/
    ClientNet_Close(serverSock);
    /*DestroyUser(&username);*/
}
/******************************************************************************************/
static int ClientManager_Register(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN], int* _logstatus, List** _userGroups)
{
 	int msgLen;
    ReqStats status = FAIL;
    char bufback[40];
    char buffer[BUFFER_LEN];
    usageDetails details;
    details.m_name = _username;
    details.m_password = _password;
    details.m_action = 1;
    while(status != REG_SUCCESS)    
    {
        msgLen = packMainMenuRequest(buffer, &details);
        ClientNet_SendMsg(_serverSock,buffer, msgLen);
        ClientNet_RcvMsg(_serverSock,bufback);
        status = unpackmainMenuAns(bufback);
        if(status != REG_SUCCESS)
        {
            ClientUI_Print(_username, REG_ERR);
			ClientUI_UserDetails(_username, _password);
        }
    }
    ClientUI_Print(_username, REG_SUCCESS);
	sleep(5);

    return 1;
}

/******************************************************************************************/
static int ClientManager_Login(int _serverSock, char _username[USERNAME_LEN], char _password[PASSWORD_LEN] ,int* logStatus, List** userGroups, int counter)
{
    int msgLen, status = -1;
    char buffer[BUFFER_LEN];
    char bufback[BUFFER_LEN];
    usageDetails details;
    details.m_name = _username;
    details.m_password = _password;
    details.m_action = LOGIN;
    while(status != LOGIN_SUCCESS) 
    {
		msgLen = packMainMenuRequest(buffer, &details);
		ClientNet_SendMsg(_serverSock,buffer, msgLen);
		ClientNet_RcvMsg(_serverSock,bufback);
		status = unpackmainMenuAns(bufback);
		if(status != LOGIN_SUCCESS)
		{
			ClientUI_Print(_username, LOGIN_ERR);
			ClientUI_Counter(counter);
			sleep(2);	
			UICleanScreen();
			return 0;
		}
		
	}
	ClientUI_Print(_username, LOGIN_SUCCESS);
    *logStatus = 1;
    *userGroups = ListCreate();
	if(*userGroups == NULL)
	{
		return 0;
	}
    return 1;
}
/************************************************************************************************************/
void destroyUserGroup(void* group)
{
	if (group != NULL)
	{
		free(((Groupids*)group)->m_groupName);
		free(group);
	}
}
/************************************************************************************************************/
static void ClientManager_RemoveAllGroups(int _serverSock, char _username[USERNAME_LEN], List** userGroups)
{
	ListItr itr, begin, end;
	Groupids* curGroup;
	usageDetails details;
	char buffer[BUFFER_LEN];
	int msgLen;
	begin  = ListItrBegin(*userGroups);
	end  = ListItrEnd(*userGroups);
	details.m_name = _username;
	details.m_action = LOG_OUT;
	
	details.m_password = NULL;
	itr = begin;
	while (!ListItrEquals(itr, end))
	{
		curGroup = (Groupids*)ListItrGet(itr);
		details.m_groupName = curGroup->m_groupName;
		msgLen = packGroupName(buffer, &details);
		ClientNet_SendMsg(_serverSock, buffer, msgLen);
		ClientNet_RcvMsg(_serverSock, buffer);
		itr = ListItrNext(itr);
		kill(curGroup->m_pidClient, SIGKILL);
		kill(curGroup->m_pidServer, SIGKILL);
		destroyUserGroup(ListItrRemove(ListItrPrev(itr)));
	}
}
/******************************************************************************************/
static void ClientManager_RemoveGroup(char _groupName[GROUP_NAME_LEN], List** userGroups)
{
	ListItr itr, begin, end;
	Groupids* curGroup;
	begin  = ListItrBegin(*userGroups);
	end  = ListItrEnd(*userGroups);
	itr = begin;
	while (!ListItrEquals(itr, end))
	{
		curGroup = (Groupids*)ListItrGet(itr);
		if (strcmp(curGroup->m_groupName, _groupName) == 0)
		{
			itr = ListItrNext(itr);
			kill(curGroup->m_pidClient, SIGKILL);
			kill(curGroup->m_pidServer, SIGKILL);
			destroyUserGroup(ListItrRemove(ListItrPrev(itr)));
			return;
		}
		itr = ListItrNext(itr);
	}
}
/******************************************************************************************/
static void ClientManager_LogOut(int _serverSock, char _username[USERNAME_LEN], int* logStatus, List** userGroups)
{
    int msgLen, status;
    char buffer[BUFFER_LEN];
    char bufback[40];
    char password[PASSWORD_LEN];
    usageDetails details;
	UserChoise choice;
    details.m_name = _username;
    details.m_password = "NULL";
    details.m_action = LOG_OUT;
    msgLen = packMainMenuRequest(buffer, &details);
    ClientNet_SendMsg(_serverSock,buffer, msgLen);
    ClientNet_RcvMsg(_serverSock,bufback);
    status = unpackmainMenuAns(bufback);
	if(status == LOG_OUT_SUCCESS)
	{
		ClientManager_RemoveAllGroups(_serverSock, _username, userGroups);
		ListDestroy(userGroups, NULL);
		ClientUI_Print(_username, LOG_OUT_SUCCESS);
		sleep(2);
	}
   *logStatus = 0;
    choice = ClientUI_HomePage();
	ClientUI_UserDetails(_username, password);


}
/******************************************************************************************/
static void ClientManager_MainMenu(int _serverSock, char _username[USERNAME_LEN],
		 UserChoise choice, int *logStatus, List** userGroups)
{
	char password[PASSWORD_LEN];
	int counter = 3;
	while(choice == REGISTER || choice == LOGIN){
		if(choice == REGISTER){
			ClientUI_UserDetails(_username, password);
			while (ClientManager_Register(_serverSock, _username, password, logStatus, userGroups) != 1){
				ClientUI_UserDetails(_username, password);
				ClientManager_Register(_serverSock, _username, password, logStatus, userGroups);
			}
			choice = ClientUI_HomePage();
		}
		if(choice == LOGIN){
			ClientUI_UserDetails(_username, password);
			while((ClientManager_Login(_serverSock, _username, password, logStatus, userGroups, counter)) != 1 && counter >0){
				ClientUI_UserDetails(_username, password);
				counter--;
			}
			if(counter == 0)
			{
				ClientManager_Run();
			}
			choice = ClientUI_GroupsMenu();
			while (choice != EXIT){
				
				ClientManager_GroupsMenu(_serverSock, _username, choice, logStatus, userGroups);
				choice = ClientUI_GroupsMenu();
			}
			/*
			if(choice == LOG_OUT)
			{
				choice = ClientUI_HomePage();
				ClientUI_UserDetails(_username, password);
			}
			*/
		}
	}
}
/******************************************************************************************/
static int join(char* _buffer, char* _groupName, char* _username, int _serverSock, List** userGroups)
{
	FILE* f1, *f2;
	char bufback[40];
	char command[100];
	char ip[IP_LEN], buffer[BUFFER_LEN];
	int msgLen, clientPID, serverPID;
	Groupids* newGroup;
	IPsAnswer answer;
	usageDetails details;
	details.m_name = _username;
	details.m_password = NULL;
	details.m_groupName = _groupName;
	details.m_action = JOIN_GROUP;
	msgLen = packGroupName(_buffer,&details);
	ClientNet_SendMsg(_serverSock, _buffer, msgLen);
	ClientNet_RcvMsg(_serverSock, bufback);
	unpackIPAns(bufback, &answer);
	if(answer.m_answer == JOIN_GROUP_ERR_ALREADY_IN)
	{
		ClientUI_Print(_username, JOIN_GROUP_ERR_ALREADY_IN);
		return 0;
	}
	else if(answer.m_answer == JOIN_GROUP_ERR_NOT_FOUND)
	{
		ClientUI_Print(_username, JOIN_GROUP_ERR_NOT_FOUND);
		return 0;
	}
	else
	strcpy(ip, answer.m_IP);
	{
		
		ClientUI_Print(_groupName ,JOIN_GROUP_SUCCESS);
		sprintf(command, "gnome-terminal --geometry 30x10-1200+50 -q -- ./Listener.out %s %s",ip, _groupName);
		system(command);

		f1 = fopen("pidS.txt","r");
		if(f1 !=NULL){
			fscanf(f1,"%d",&serverPID);
			fclose(f1);
		}

		sprintf(command, "gnome-terminal --geometry 30x5-1200+500 -q -- ./Sender.out %s %s %s",ip, _username, _groupName);
		system(command);

		f2 = fopen("pidC.txt","r");
		if(f1 !=NULL){
			fscanf(f2,"%d",&clientPID);
			fclose(f2);
		}

		newGroup = (Groupids*)malloc(sizeof(Groupids));
		newGroup->m_groupName = (char*)malloc(strlen(_groupName)+1);
		strcpy(newGroup->m_groupName, _groupName);
		newGroup->m_pidClient = clientPID;
		newGroup->m_pidServer = serverPID;
		
		ListPushHead(*userGroups, newGroup);
		return 1;
	}
}
/******************************************************************************************/
static void ClientManager_LeaveGroup(int _serverSock, List** userGroups, char _username[USERNAME_LEN])
{
	int msgLen;
	char buffer[BUFFER_LEN];
	char groupName[GROUP_NAME_LEN];
	usageDetails details;
	ReqStats status;
	ClientUI_groupDetails(groupName);
	details.m_groupName = groupName;
	details.m_name = _username;
	details.m_password = NULL;
	details.m_action = LEAVE_GROUP;
	msgLen = packGroupName(buffer, &details);
	ClientNet_SendMsg(_serverSock, buffer, msgLen);
	ClientNet_RcvMsg(_serverSock, buffer);
	status = unpackmainMenuAns(buffer);
	if(status == LEAVE_GROUP_ERR)
	{
		ClientUI_Print(_username, LEAVE_GROUP_ERR);
	}
	else
	{
		ClientManager_RemoveGroup(groupName, userGroups);
		ClientUI_Print(groupName, LEAVE_GROUP_SUCCESS);
	}
}
/******************************************************************************************/
static void ClientManager_ShowGroups(int _serverSock, char* _username)
{	usageDetails details;
	char buffer[BUFFER_LEN];
	char bufback[BUFFER_LEN];
	ReqStats status;
	char* group;
	int msgLen;
	Vector *vectorBack = VectorCreate(10,10);
	if(vectorBack == NULL){
		return ;
	}
	details.m_name = _username;
	details.m_action = SHOWGROUPS;
	msgLen = packshowgroupsReq(buffer, &details);
	ClientNet_SendMsg(_serverSock,buffer, msgLen);
	ClientNet_RcvMsg(_serverSock, bufback);
	unpackshowgroupsAns(bufback,vectorBack);

	while(VectorRemove(vectorBack, (void**) &group) == VECTOR_SUCCESS)
	{
		printf("%s \n", group);

	}
	VectorDestroy(&vectorBack, NULL);
}
/******************************************************************************************/
static void ClientManager_GroupsMenu(int _ServerSock, char _username[USERNAME_LEN], UserChoise choice, int *logStatus, List** userGroups)
{
	switch (choice)
	{
	
		case CREATE_GROUP:
			ClientManager_CreateGroup(_ServerSock, _username, userGroups);
			break;
		
		case JOIN_GROUP:
			ClientManager_ShowGroups(_ServerSock, _username);
			ClientManager_JoinGroup(_ServerSock, _username, userGroups);
			break;			 
		case LEAVE_GROUP:
			ClientManager_LeaveGroup(_ServerSock, userGroups,_username);
			break;
		case LOG_OUT:
			ClientManager_LogOut(_ServerSock, _username, logStatus, userGroups);
			break;

		default :
			break;
	}
}
/******************************************************************************************/
static void ClientManager_JoinGroup(int _ServerSock, char _username[USERNAME_LEN], List** _userGroups)
{
	int answer;
	char groupName[USERNAME_LEN];
	char buffer[BUFFER_LEN];
	ClientUI_groupDetails(groupName);
	answer = join(buffer, groupName, _username, _ServerSock, _userGroups);
	while(!answer)
	{
		ClientUI_groupDetails(groupName);
		answer = join(buffer, groupName, _username, _ServerSock, _userGroups);
	}
}
/******************************************************************************************/
static void ClientManager_CreateGroup(int _serverSock, char _username[USERNAME_LEN], List** _userGroups)
{
	int answer;
	char groupName[USERNAME_LEN];
	char buffer[BUFFER_LEN];

	ClientUI_groupDetails(groupName);
	answer = createGroup (buffer, groupName, _username, _serverSock, _userGroups);	
	while(!answer)
	{
		ClientUI_groupDetails(groupName);
		answer = createGroup (buffer, groupName, _username, _serverSock, _userGroups);	
	}
}
/******************************************************************************************/
static int createGroup(char* _buffer, char* _groupName, char* _username, int _serverSock, List** userGroups)
{
	char bufback[40];
	char command[100];
	usageDetails details;
	IPsAnswer answer;
	FILE* f1, *f2;
	char ip[IP_LEN];
	int msgLen, clientPID, serverPID;
	Groupids* newGroup;
	details.m_name = _username;
        details.m_password = NULL;
	details.m_groupName = _groupName;
 	details.m_action = CREATE_GROUP;
	msgLen = packGroupName(_buffer, &details);

	ClientNet_SendMsg(_serverSock, _buffer, msgLen);
	ClientNet_RcvMsg(_serverSock, bufback);
	unpackIPAns(bufback, &answer);

	if(answer.m_answer == CREATE_GROUP_ERR)
	{
		ClientUI_Print(_groupName, CREATE_GROUP_ERR);
		return 0;
	}
	else
	strcpy(ip, answer.m_IP);
	{
		printf("You joined group : %s!\n", _groupName);

			sprintf(command, "gnome-terminal --geometry 30x10-1200+50 -q -- ./Listener.out %s %s",ip, _groupName);
			system(command);

			f1 = fopen("pidS.txt","r");
			if(f1 != NULL){
				
				fscanf(f1,"%d",&serverPID);
				fclose(f1);
			}

			sprintf(command, "gnome-terminal --geometry 30x5-1200+500 -q -- ./Sender.out %s %s %s",ip, _username, _groupName);
			system(command);

			f2 = fopen("pidC.txt","r");
			if(f2 != NULL){
				fscanf(f2,"%d",&clientPID);
				fclose(f2);
			}
		newGroup = (Groupids*)malloc(sizeof(Groupids));
		newGroup->m_groupName = (char*)malloc(strlen(_groupName)+1);
		strcpy(newGroup->m_groupName, _groupName);
		newGroup->m_pidClient = clientPID;
		newGroup->m_pidServer = serverPID;
		ListPushHead(*userGroups, newGroup);
		return 1;
	}
}


