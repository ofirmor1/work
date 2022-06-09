#include <stdlib.h>
#include "HashMap.h"
#include "ServerManager.h"
#include "VectorGeneric.h"
#include "UserManager.h"
#include "User.h"
#include "Protocols.h"
#include <stdio.h>
#include "GenericServer.h"
#include "GroupsManager.h"
#include "GenericDouble.h"
#include "Chat.h"
#define MAXUSERS 100
#define NOT_EQUAL 0
#define EQUAL 1
void failMsg(Server *_myServer, int error);
void GotMsg(Server *_myServer,void *msg, int clientID, void* _context1, void* _context2);
size_t HashFunctionByName(const void* _data);
int EqualityFunctionByName(const void* _currKey, const void* _searchKey);
int regisNewUser(struct usageDetails *details, void* bufBack, UsersManager* userManager);

void InitServerManager(){
	Server* myServerNet;
	UsersManager* userManager;
	GroupsManager* groupManager;
	servParams parm;
	parm.GotMessage = GotMsg;
	parm.checkClient = NULL;
	parm.closeClient = NULL;
	parm. failMessage = failMsg;
	parm.MaxClient = 1000;
	userManager = CreateUsersManager(MAXUSERS,HashFunctionByName, EqualityFunctionByName);
	groupManager = CreateGroupsManager(HashFunctionByName, EqualityFunctionByName);
	myServerNet = createServerNet(&parm, (void*)userManager, (void*)groupManager);
	RunServer(myServerNet);
}

int manageRequests(void *_buffer, void* _bufback, void* _context1, void* _context2, int _clientID){
	int reqNumber;
	struct usageDetails *details;
	struct IPsAnswer *IPdetails;
	details = (struct usageDetails*) malloc(sizeof(struct usageDetails));
	if(details == NULL){
		return -1;
	}
	IPdetails = (struct IPsAnswer*) malloc(sizeof(struct IPsAnswer));
	if(IPdetails == NULL){
		return -1;
	}
	IPdetails -> m_answer = -1;
	IPdetails -> m_port = 0;
	IPdetails -> m_IP = 0;
	reqNumber = openMessage(_buffer, details);
	if(reqNumber == REGISTER){
		return regisNewUser(details, _bufback, (UsersManager*)_context1);
	}
	else if(reqNumber == LOGIN){
	 	return LogInUser(details,_bufback, (UsersManager*)_context1, _clientID);
	}
	else if(reqNumber == CREATE_GROUP){
		return createGroup(IPdetails, details, _bufback, (UsersManager*)_context1, (GroupsManager*)_context2);
	}
	else if(reqNumber == SHOWGROUPS){
		return showGroups(details, _bufback,(GroupsManager*)_context2);
	}
	else if(reqNumber == JOIN_GROUP){
		return joinGroup(IPdetails, details, _bufback,  (UsersManager*)_context1, (GroupsManager*)_context2);
	}
	else if(reqNumber == LEAVE_GROUP){
		return leaveGroup(IPdetails, details, _bufback,  (UsersManager*)_context1, (GroupsManager*)_context2);
	}
	else if(reqNumber == LOG_OUT)
	{
		return LogOutUser(details, _bufback, (UsersManager*)_context1, (GroupsManager*)_context2,  _clientID);
	}
}
	
int regisNewUser(struct usageDetails *details, void* bufBack, UsersManager* userManager){
	ReqStats answer;
	int msg_len;

	answer = Register(userManager, details -> m_name, details -> m_password);
	printf("This is Register name - %s\n", details -> m_name);
	printf("This is Register password - %s\n", details -> m_password);
	printf("This is Register amswer -  %d\n", answer);
	msg_len = packmainMenuAns((void*)bufBack, answer);
	destroyUsageDetails(&details);
	return msg_len;
}
	
int LogInUser(struct usageDetails *details, void* bufBack, UsersManager* userManager, int _clientID){
	ReqStats answer;
	int msg_len;
	answer = UserLogIn(userManager, details -> m_name, details -> m_password, _clientID);
	printf("This is login name - %s\n", details -> m_name);
	printf("This is login password - %s\n", details -> m_password);
	printf("This is login amswer - %d\n", answer);
	msg_len = packmainMenuAns((void*)bufBack, answer);
	destroyUsageDetails(&details);
	return msg_len;
}


int LogOutUser(struct usageDetails *details, void* bufBack, UsersManager* userManager, GroupsManager * _groupManager ,int _clientID)
{
	ReqStats answer;
	int msg_len;
	List * userGroups = GetGroupsListByUserName(userManager, details->m_name);
	GroupUserLogOut( _groupManager, userGroups);
	answer = UserLogOut(userManager, &_clientID);
	msg_len = packmainMenuAns((void*)bufBack, answer);
	destroyUsageDetails(&details);
	return msg_len;
}


int createGroup(struct IPsAnswer *IPdetails,struct usageDetails *_details,
 	void* _bufBack, UsersManager* _userManager, GroupsManager *_groupsManager){

	ReqStats answer; 
	int msg_len; 
	char * IP;
	IP = (char*)malloc(15);/*TODO complete*/
	answer = getGroupIP(_groupsManager, _details -> m_groupName, IP);
	if(answer == FOUND){
		IPdetails -> m_answer = CREATE_GROUP_ERR;
		msg_len = packIPAns((void*)_bufBack, IPdetails);
		destroyUsageDetails(&_details);
		return msg_len;
	}

	answer = CreateNewGroup(_groupsManager, _details -> m_groupName, IP);
	IPdetails -> m_answer = answer;
	if(answer == CREATE_GROUP_ERR){
		msg_len = packIPAns((void*)_bufBack,IPdetails);
		destroyUsageDetails(&_details);
		return msg_len;
	}
	UserJoinGroup(_userManager, _details -> m_name, _details -> m_groupName);
	IPdetails -> m_port = GetPortByGroupName(_groupsManager, _details -> m_groupName);
	IPdetails -> m_IP = IP;
	msg_len = packIPAns((void*)_bufBack, IPdetails);
	destroyUsageDetails(&_details);
	return msg_len;
}


int joinGroup(struct IPsAnswer *IPdetails, struct usageDetails *_details, void* _bufBack, UsersManager* _userManager, GroupsManager *_groupsManager)
{
	ReqStats answer; 
	int msg_len;
	char * IP;
	IP = (char*)malloc(15);/*TODO complete*/
	answer = UserJoinGroup(_userManager, _details -> m_name, _details -> m_groupName);
	IPdetails -> m_answer = answer;
	if(answer == JOIN_GROUP_ERR_ALREADY_IN)
	{	
		msg_len = packIPAns(_bufBack, IPdetails);
		destroyUsageDetails(&_details);
		return msg_len;
	}

	answer = getGroupIP(_groupsManager, _details -> m_groupName, IP);
	if(answer == NOT_FOUND)
	{ 
		IPdetails -> m_answer = JOIN_GROUP_ERR_NOT_FOUND;
		msg_len = packIPAns((void*)_bufBack, IPdetails);
		destroyUsageDetails(&_details);
		return msg_len;
	}
	IPdetails -> m_answer = JOIN_GROUP_SUCCESS;
	AddCountGroupNumOfMember(_groupsManager, _details -> m_groupName);
	IPdetails -> m_port = GetPortByGroupName(_groupsManager, _details -> m_groupName);
	IPdetails -> m_IP = IP;
	msg_len = packIPAns(_bufBack,IPdetails);
	destroyUsageDetails(&_details);
	return msg_len;
}

int leaveGroup(struct IPsAnswer *IPdetails, struct usageDetails *_details, void* _bufBack, UsersManager* _userManager, GroupsManager *_groupsManager)
{
	ReqStats answer; 
	int msg_len;

	answer = LeaveTheGroup(_userManager, _details -> m_name, _details -> m_groupName);
	IPdetails -> m_answer = answer;
	if(answer == LEAVE_GROUP_ERR)
	{	
	msg_len = packmainMenuAns(_bufBack, answer);
		destroyUsageDetails(&_details);
		return msg_len;
	}
	printf("%d\n", answer);
	LessCountGroupNumOfMember(_groupsManager, _details -> m_groupName);
	msg_len = packmainMenuAns(_bufBack, answer);
	destroyUsageDetails(&_details);
	return msg_len;
}

int showGroups(struct usageDetails *_details, void* _bufBack,GroupsManager *_groupsManager){
	int msg_len;
	Vector* groupsName = VectorCreate(10,10);
	if(groupsName == NULL){
		return -1;
	}
	GetGroupsList(_groupsManager, groupsName);
	msg_len = packTheGroups(_bufBack, groupsName);
	VectorDestroy(&groupsName, NULL);
	return msg_len;
}


void GotMsg(Server *_myServer,void *msg, int clientID, void* _context1, void* _context2){
	int msg_len;
	char* bufBack = (char*) malloc(sizeof(char*));

	if(bufBack == NULL){
		return;
	}
	msg_len = manageRequests(msg, bufBack, _context1, _context2, clientID);
	sendMessage(_myServer,clientID, bufBack, msg_len);
}

size_t HashFunctionByName(const void* _data)
{
	return (*(char*)_data) * 2;
}

int EqualityFunctionByName(const void* _currKey, const void* _searchKey)
{
	if(strcmp((char*)_currKey, (char*)_searchKey) == 0)
	{
		return EQUAL;
	}
	return NOT_EQUAL;
}	
	

void failMsg(Server *_myServer, int error){
	printf("This is failure\n");
}



main(){
	InitServerManager();
}
	

