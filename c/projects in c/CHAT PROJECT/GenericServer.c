#include "GenericServer.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "GenericDouble.h"
#include "Iterator.h"
#include <sys/select.h>
#define PORT 2000
#define BACKLOG 500
#define MAX_FD 1023
#define SUCCESS 0
#define FAIL -1
#define MAXCONNECTS 1000



struct Server{
	Got_msg		 m_GotMessageFunc;
	Check_new_client m_checkClientFunc;
	close_client 	 m_closeClientFunc;
	fail 	 	 m_failMessageFunc;
	int 		 m_MaxClient;
	List*		 m_ClientList;
	int 		 m_listenSocket;
	fd_set    	 m_masterFD;
	fd_set 		 m_tmpFD;
	int 		 m_runningFlag;
	int 		 m_numOfCLients;
	void*		 m_context1;
	void*		 m_context2;
};
/***********************************internal declaration function************************************************/
int initialServer(struct sockaddr_in sin, int sock);
int connectToServer(struct sockaddr_in sin, int sock);
int checknewCLient(struct sockaddr_in sin, Server *_myServer);
int readingFromClient(Server *_myServer, int client_sock, char buffer[], int expected_data_len);
void checkCurrCLients(Server *_myServer, int _activity);
int sendingToClient(int client_sock, char *data_addr, int data_len);
void destroyClient(void *currClient);

/*************************************API functions*************************************************************/
Server* createServerNet(struct servParams *_parameters, void *_context1, void *_context2)
{
	fd_set master, tmp;
	List *newList;
	Server *newServer;
	struct sockaddr_in sin;
	int listen_socket, initStatus;
	if(_parameters == NULL){
		return NULL;
	}
	if(_parameters -> GotMessage == NULL || _parameters -> failMessage == NULL || _parameters -> MaxClient <= 0 ||
	_parameters -> MaxClient > MAXCONNECTS){
		return NULL;
	}
	newServer = (Server*) malloc(sizeof(Server));
	if(newServer == NULL){
		return NULL;
	}
	if((newList = ListCreate()) == NULL){
		free(newServer);
		return NULL;
	}
	newServer -> m_GotMessageFunc = _parameters -> GotMessage;
	newServer -> m_checkClientFunc =  _parameters -> checkClient;
	newServer -> m_closeClientFunc = _parameters -> closeClient;
	newServer -> m_failMessageFunc = _parameters -> failMessage;
	newServer -> m_MaxClient = _parameters -> MaxClient;
	newServer -> m_ClientList = newList;
	newServer -> m_runningFlag = 0;
	newServer -> m_numOfCLients = 0;
	newServer -> m_context1 = _context1;
	newServer -> m_context2 = _context2;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);

	if((listen_socket = socket(AF_INET, SOCK_STREAM,0)) < 0){
		return NULL;
	}
	newServer -> m_listenSocket = listen_socket;

	FD_ZERO(&master);
	FD_SET(newServer -> m_listenSocket, &master);
	
	if(initialServer(sin, newServer -> m_listenSocket) == FAIL){
		return NULL;
	}
	newServer -> m_masterFD = master;
	newServer -> m_tmpFD = master;
	return newServer;
}
	

SERVER_ERRORS RunServer(Server *_myServer){
	struct sockaddr_in sin;
	int activityNum, client_sock;
	int *Val;
	if(_myServer == NULL){
		return SERVER_NOT_INITIALIZED;
	}
	_myServer -> m_runningFlag = 1;
	while(_myServer -> m_runningFlag == 1){
		_myServer -> m_tmpFD = _myServer -> m_masterFD;
		activityNum = select(MAX_FD+1, &_myServer -> m_tmpFD, NULL, NULL, NULL);

		if(FD_ISSET(_myServer -> m_listenSocket, &_myServer -> m_tmpFD)){
			if((client_sock = checknewCLient(sin, _myServer)) > 0){ /*legal client */
				if (_myServer -> m_numOfCLients >= _myServer -> m_MaxClient){ 
					/*case the server full*/		
					close(client_sock);
					_myServer -> m_failMessageFunc(_myServer, SERVER_OVERFLOW);
				}
				else{/*client sock is legal and there is place in queue server*/
					if((Val = (int*) malloc(sizeof(int))) == NULL){
						_myServer -> m_failMessageFunc(_myServer, SERVER_FATAL_ERROR);
					
					}
					*Val = client_sock;
					FD_SET(client_sock, &_myServer -> m_masterFD);
					ListPushHead( _myServer->m_ClientList ,Val);
					_myServer -> m_numOfCLients++;
				}

			}
			/*if(activityNum > 0){*/	
		}
		checkCurrCLients(_myServer, activityNum);
	}
}

SERVER_ERRORS sendMessage(Server *_myServer, int clientId, void* info, int dataLen){
	if(_myServer == NULL){
		return SERVER_NOT_INITIALIZED;
	}
	if(sendingToClient(clientId, info, dataLen) == FAIL){
		_myServer -> m_failMessageFunc(_myServer, SENDING_ERROR);
		return SENDING_ERROR;
	}	
	return SERVER_SUCCESS;
}


void destroyServer(Server **_myServer){
	if(_myServer == NULL || *_myServer == NULL){
		return;
	}
	ListDestroy(&((*_myServer) -> m_ClientList), destroyClient);	
	close((*_myServer) -> m_listenSocket);
	free(*_myServer);
	*_myServer = NULL;
}

void StopServer(Server *_myServer){
	if(_myServer == NULL){
		return;
	}
	_myServer -> m_runningFlag = 0;
}

/************************************************internal FUnctions****************************************/
int initialServer(struct sockaddr_in sin, int sock){
	int optval = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0) {
		return FAIL;
	}
	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		return FAIL;
	}
	if (listen(sock, BACKLOG) < 0) {
		return FAIL;
	}
	return SUCCESS;
}

int connectToServer(struct sockaddr_in sin, int sock){
	int flag;
	socklen_t addr_len = sizeof(sin);
	int client_sock;
	client_sock = accept(sock,(struct sockaddr *) &sin ,&addr_len);
	return client_sock;
}


int checknewCLient(struct sockaddr_in sin, Server *_myServer){
	int client_sock;
	client_sock = connectToServer(sin, _myServer -> m_listenSocket);
	if(client_sock < 0){
		_myServer -> m_failMessageFunc(_myServer, SERVER_FATAL_ERROR);
		/*?*/return FAIL;
	}
	if(_myServer -> m_checkClientFunc != NULL){ 
		if((_myServer -> m_checkClientFunc(client_sock)) == SERVER_NEWCLIENT_ILLEGAL){
			close(client_sock);
			return FAIL;
		}
		else{
			return client_sock;
		}
	}
	return client_sock;
}

int readingFromClient(Server *_myServer, int client_sock, char buffer[], int expected_data_len){
	int read_bytes;
	read_bytes = recv(client_sock, buffer, expected_data_len, 0);
	if (read_bytes == 0){
		return FAIL;
	}
	else if (read_bytes < 0) { 
		_myServer -> m_failMessageFunc(_myServer, RECIEVE_ERROR);
		return FAIL;
	}
	printf("%s\n", buffer);
	return SUCCESS;
}

void checkCurrCLients(Server *_myServer, int _activity){
	ListItr begin = ListItrBegin(_myServer -> m_ClientList), end = ListItrEnd(_myServer -> m_ClientList);
	ListItr tmpItr, curr = begin;
	int *currClient;
	char buffer[4096];
	int expected_data_len = sizeof(buffer);
	while(curr!=end && _activity > 0){
		currClient = ListItrGet(curr);
		if(FD_ISSET(*currClient, &_myServer -> m_tmpFD)){	
			_activity--;
			/*recieving message*/
			if(readingFromClient(_myServer, *currClient, buffer, expected_data_len) == FAIL){ 
				tmpItr = ListItrNext(curr);	
				ListItrRemove(curr);
				curr = tmpItr;
				FD_CLR(*currClient, &_myServer -> m_masterFD);
				if(_myServer -> m_closeClientFunc !=NULL){
					_myServer -> m_closeClientFunc(*currClient);
				}
				close(*currClient);
				free(currClient);
				_myServer -> m_numOfCLients--;
			}
			else{
				_myServer -> m_GotMessageFunc(_myServer, buffer, *currClient, _myServer -> m_context1, 
_myServer -> m_context2); /*for sending*/
				curr = ListItrNext(curr);
			}	
		}		
		curr = ListItrNext(curr);
	}
}

int sendingToClient(int client_sock, char *data_addr, int data_len){
	int sent_bytes;
	sent_bytes = send(client_sock, data_addr, data_len, 0);
	if (sent_bytes < 0) {
		return FAIL;
	}
	return SUCCESS;
}

void destroyClient(void *currClient){
	close(*(int*)currClient);
}

