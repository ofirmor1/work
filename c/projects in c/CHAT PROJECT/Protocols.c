#include "Protocols.h"
#include "Chat.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "VectorGeneric.h"
#define IP_LENGTH 11

void unpackNamePassword(void* buffer, struct usageDetails *req);
int packNamePassword(void *buffer, struct usageDetails *_userDets);
int packLogoutReq(void *buffer, struct usageDetails *_userDets);
void unpackLogoutReq(void *buffer, struct usageDetails *_userDets);

int openMessage(void *buffer, struct usageDetails *_userDets){
	int req = ((char*)buffer)[0];
	if(req ==REGISTER|| req == LOGIN|| req == LOG_OUT){
	 	unpackNamePassword(buffer,_userDets);
		return req;
	}
	if(req == CREATE_GROUP || req == JOIN_GROUP || req == LEAVE_GROUP){
		unpackGroupName(buffer,_userDets);
		return req;
	}
}

int packMainMenuRequest(void *buffer, struct usageDetails *_userDets){
	if(_userDets -> m_action == 1/*regis*/ || _userDets -> m_action == 2/*login*/ ||  _userDets -> m_action == LOG_OUT){
		return packNamePassword(buffer,_userDets);
	}
	else if(_userDets -> m_action == 3 /*logout*/){
		return packLogoutReq(buffer,_userDets);
	}
}

void unpackMainMenuRequest(void *buffer, struct usageDetails *_req){
	if(_req -> m_action == 1/*regis*/ || _req -> m_action == 2/*login*/){
		unpackNamePassword(buffer, _req);
	}
	else if(_req -> m_action == 3 /*logout*/){
		unpackLogoutReq(buffer,_req);
	}
}	

/* ans,length tot, length port, port,length IP, IP*/
int packIPAns(void *buffer,struct IPsAnswer *IPsDetails){

	char bufIdx = 0;
	char answer = (char)IPsDetails -> m_answer;
	/*TODO fix if recive ALREADY_IN_ERR*/
	char portLen = strlen(IPsDetails -> m_port);
	char IpsLen = strlen(IPsDetails -> m_IP);
	char tot_length = sizeof(char)*4 + portLen + IpsLen;

	memcpy((char*)buffer, &answer, sizeof(char));
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, &tot_length, sizeof(tot_length));
	bufIdx = bufIdx +sizeof(tot_length);

	memcpy((char*)buffer+bufIdx, &portLen, sizeof(portLen));
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, IPsDetails -> m_port, portLen);
	bufIdx = bufIdx +portLen;

	memcpy((char*)buffer+bufIdx, &IpsLen, sizeof(IpsLen));
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx,IPsDetails -> m_IP,IpsLen);
	bufIdx = bufIdx + IpsLen;
	
	return bufIdx;
}

void unpackIPAns(void *buffer,struct IPsAnswer *IPsDetails){
	char portLen, IPLen;
	portLen = ((char*)buffer)[sizeof(char)*2];
	IPLen = ((char*)buffer)[sizeof(char)*2+portLen+1];

	IPsDetails -> m_answer = ((char*)buffer)[0];
	IPsDetails -> m_IP = (char*)malloc(IPLen+1);
	IPsDetails -> m_port = (char*)malloc(portLen+1);

	memcpy(IPsDetails-> m_port,((char*)buffer)+sizeof(char)*3 ,portLen);
	memcpy(IPsDetails-> m_IP,  ((char*)buffer)+sizeof(char)*4 +portLen,IPLen);
}

void unpackNamePassword(void* buffer, struct usageDetails *req){
	char nameLen, PassLen;
	nameLen = ((char*)buffer)[sizeof(char)*2];
	PassLen = ((char*)buffer)[sizeof(char)*2+nameLen+1];

	req-> m_action = ((char*)buffer)[0];
	req-> m_name = (char*)malloc(nameLen+1);
	req-> m_password = (char*)malloc(PassLen+1);

	memcpy(req-> m_name, ((char*)buffer)+sizeof(char)*3 ,nameLen);
	memcpy(req-> m_password, ((char*)buffer)+sizeof(char)*4 +nameLen ,PassLen);
}

/*Ans*/
int packmainMenuAns(void *buffer, int _answer){
	((char*)buffer)[0] = _answer;
	return 1;
}

ReqStats unpackmainMenuAns(void *buffer){
	return (ReqStats)((char*)buffer)[0];
}

/*action, tot_length,nameLength, name, groupNameLength, groupName*/ /*function for join, create and leave chat*/
int packGroupName(void *buffer, struct usageDetails *_userDets){
	char bufIdx = 0;
	char countExtraBytes = sizeof(char)*4;
	char lenName = strlen(_userDets -> m_name);
	char lenGroupName = strlen(_userDets -> m_groupName);
	char tot_length = lenGroupName + countExtraBytes +lenName;

	memcpy((char*)buffer, &_userDets -> m_action, sizeof(_userDets -> m_action));
	bufIdx = bufIdx +sizeof(char);
	
	memcpy((char*)buffer+bufIdx, &tot_length, sizeof(tot_length));
	bufIdx = bufIdx +sizeof(char);
	
	memcpy((char*)buffer+bufIdx, &lenName, sizeof(lenName));
	bufIdx = bufIdx +sizeof(lenName);
	
	memcpy((char*)buffer+bufIdx,_userDets -> m_name,lenName);
	bufIdx = bufIdx + lenName;

	memcpy((char*)buffer+bufIdx, &lenGroupName, sizeof(lenGroupName));
	bufIdx = bufIdx + sizeof(lenGroupName);

	memcpy((char*)buffer+bufIdx,_userDets -> m_groupName,lenGroupName);
	bufIdx = bufIdx + lenGroupName;
	return bufIdx;
}

void unpackGroupName(void *buffer, struct usageDetails *_userDets){
	int nameLen, groupLen;
	nameLen = ((char*)buffer)[sizeof(char)*2];
	groupLen = ((char*)buffer)[sizeof(char)*2+nameLen+1];

	_userDets-> m_action = ((char*)buffer)[0];
	_userDets-> m_groupName = (char*)malloc(sizeof(char*));
	_userDets-> m_name = (char*)malloc(sizeof(char*));

	memcpy(_userDets-> m_name, ((char*)buffer)+sizeof(char)*3 ,nameLen);
	memcpy(_userDets-> m_groupName, ((char*)buffer)+sizeof(char)*4 +nameLen ,groupLen);
}

/*action, tot_length, namelength, name, passlength, pass*/
int packNamePassword(void *buffer, struct usageDetails *_userDets){

	char countExtraBytes = sizeof(char)*4;
	char lenName = strlen(_userDets -> m_name);
	char lenPass = strlen(_userDets -> m_password);
	char tot_length = lenName + lenPass + countExtraBytes;
	char bufIdx = 0;

	memcpy((char*)buffer, &_userDets -> m_action, sizeof(_userDets -> m_action)); /*tag*/
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, &tot_length, sizeof(tot_length)); /*total length*/
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, &lenName, sizeof(lenName)); /*name length*/
	bufIdx = bufIdx + sizeof(lenName);

	memcpy((char*)buffer+bufIdx,_userDets -> m_name,lenName); /*name*/
	bufIdx = bufIdx + lenName;

	memcpy((char*)buffer+bufIdx,&lenPass, sizeof(lenPass));	/*password length*/
	bufIdx = bufIdx + sizeof(lenPass);

	memcpy((char*)buffer+bufIdx, _userDets -> m_password, lenPass); /*password*/
	bufIdx = bufIdx + lenPass;

	return bufIdx;
}

int packLogoutReq(void *buffer, struct usageDetails *_userDets){
	int bufIdx = 0;
	memcpy((char*)buffer, &_userDets -> m_action, sizeof(_userDets -> m_action));
	printf("%d",( (char*)buffer)[bufIdx]);
	bufIdx++;
	return bufIdx;
}

void unpackLogoutReq(void *buffer, struct usageDetails *_userDets){
	_userDets-> m_action = ((char*)buffer)[0];
}

/*action, tot length, len name, name*/
int packshowgroupsReq(void *buffer, struct usageDetails *_userDets){ /*client side*/
	char countExtraBytes = sizeof(char)*3;
	char lenName = strlen(_userDets -> m_name);
	char tot_length = lenName + countExtraBytes;
	char bufIdx = 0;
	
	memcpy((char*)buffer, &_userDets -> m_action, sizeof(_userDets -> m_action)); /*tag*/
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, &tot_length, sizeof(tot_length)); /*total length*/
	bufIdx = bufIdx +sizeof(char);

	memcpy((char*)buffer+bufIdx, &lenName, sizeof(lenName)); /*name length*/
	bufIdx = bufIdx + sizeof(lenName);

	memcpy((char*)buffer+bufIdx,_userDets -> m_name,lenName); /*name*/
	bufIdx = bufIdx + lenName;

	return bufIdx;
}

/**/
/*length, name, length, name....*/
int packTheGroups(void* _buffer, Vector* groupsName){ /*server side*/
	int i, numofGroups = VectorSize((void*)groupsName);
	char* tmp = (char*) malloc(sizeof(char*));
	char* array =(char*) malloc(numofGroups*sizeof(char));
	char bufIdx =0;
	char tot = numofGroups+1;
	for(i = 0 ; i < numofGroups; i++){
		VectorGet(groupsName, i, (void*)&tmp);
		array[i] = strlen(tmp);
		tot = tot +array[i];
	}
	memcpy((char*)_buffer+bufIdx, &tot, sizeof(char));
	bufIdx =bufIdx + sizeof(char);

	for(i = 0 ; i < numofGroups; i++){
		VectorGet(groupsName, i, (void*)&tmp);	
		memcpy((char*)_buffer+bufIdx,&array[i],sizeof(char)); /*len*/
		bufIdx = bufIdx +sizeof(char);
		memcpy((char*)_buffer+bufIdx,tmp,array[i]); /*name*/
		bufIdx = bufIdx +array[i];
	}
	return bufIdx;
}
/**/
void unpackshowgroupsAns(void* _buffer, Vector* groupsName){ /*server side*/
	char bufIdx = 0;
	char len;
	char *tmp; 
	char total = ((char*)_buffer)[0];
	bufIdx = bufIdx +1;
	while(bufIdx <= total){
		len = ((char*)_buffer)[bufIdx];
		tmp = (char*) malloc(sizeof(char)*len);
		memcpy(tmp, ((char*)_buffer)+bufIdx+1 ,len);
		VectorAppend(groupsName, tmp);
		bufIdx = bufIdx + len + 1;
	}
}

void destroyUsageDetails(struct usageDetails **_userDets){
	if(_userDets == NULL || *_userDets == NULL){
		return;
	}
	free((*_userDets) -> m_name);
	free((*_userDets) -> m_password);
	free(*_userDets);
	*_userDets = NULL;
}



