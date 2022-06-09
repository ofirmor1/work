#ifndef __PROTOCOLS_H__
#define __PROTOCOLS_H__
#include "Chat.h"
#include "VectorGeneric.h"


typedef struct usageDetails{
	char*		 m_name;
	char*		 m_password;
	char* 	        m_groupName;
	UserChoise		m_action;
}usageDetails;

typedef struct IPsAnswer{
	char*	 m_IP;	
	ReqStats  	 m_answer;
	char*          m_port;

}IPsAnswer;


int openMessage(void *buffer, struct usageDetails *_userDets);
/*****client side*****/
/*Description: this function destroy the details struct after usage. 
Input:pointer to the user details struct 
Output:void
Error: none*/
void destroyUsageDetails(struct usageDetails **_userDets);

/*****client side*****/
/*Description: this function calling two internal another functions:
1. if the flag is REGISRATION or LOGIN calling the function which pack the name and password.
2. if flag is LOGOUT caliing function packed only the request. (flag).
Input:pointer to empty buffer to fill and struct contains the name, passowrd and action.
Output: buffer length after filling.
Error: none*/
int packMainMenuRequest(void *buffer, struct usageDetails *_userDets);

/*****server side*****/
/*Description: this function calling two internal another functions:
1. if the flag is REGISRATION or LOGIN calling the function which unpack the name and password
2. if flag is LOGOUT caliing function unpack only the request. (flag).
Input:pointer to the buffer(contains the info) and struct to fill the details inside.
Output: void
Error: none*/
void unpackMainMenuRequest(void *buffer, struct usageDetails *_req);

/*****client side*****/
/*Description: this function packing the request(create/leave/join). 
Input: pointer to the buffer(contains the info) and struct to fill the details inside.
Output: buffer length after filling.
Error: none*/
int packGroupName(void *buffer, struct usageDetails *_userDets);

/*****server side*****/
/*Description: this function unpack the request 
Input:pointer to the buffer(contains the info) and struct to fill the details inside.
Output: void
Error: none*/
void unpackGroupName(void *buffer, struct usageDetails *_userDets);

/*****server side*****/
/*Description: this function pack the answer from server (for register. login, logout). 
Input:pointer to the enpty buffer and the answer.
Output: buffer length after filling.
Error: none*/
int packmainMenuAns(void *buffer, int _answer);

/*****client side*****/
/*Description: this function unpack the answer from server (for register. login, logout). 
Input:pointer to the buffer(contains the info)
Output: the answer after unpacking.
Error: none*/
ReqStats unpackmainMenuAns(void *buffer);


void unpackIPAns(void *buffer,struct IPsAnswer *IPsDetails);


int packIPAns(void *buffer,struct IPsAnswer *IPsDetails);

void unpackshowgroupsAns(void* _buffer, Vector* groupsName); /*server side*/
#endif


