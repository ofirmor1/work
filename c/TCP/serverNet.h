/*#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h> /*FD_SET,FD_ZERO
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../DS/genericDll.h"
#include "../DS/list_functions.h"
#include "../DS/list_Itr.h"*/

/**************************************************************************************/
typedef void (*NewClient)();
typedef void (*GotMsg)(int cliendId, char* buffer, int messageSize);
typedef void (*CloseClient)(int sock);
typedef void (*Fail)();
typedef void (*StopRun)(int stopRun);

typedef struct Server Server;

/**************************************************************************************/
Server* ServerCreate(NewClient newClientFunc, GotMsg gotMsgFunc, CloseClient closeClientFunc, Fail failFunc,StopRun stopRunFunc, int maxClients);
/**************************************************************************************/
Server* ServerRun(Server* server);
/**************************************************************************************/
void ServerSendMessage(Server* server, int clientSock, char* message, int messageSize);
/**************************************************************************************/
void ServerDestroy(Server** server);
