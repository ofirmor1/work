#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h> /*FD_SET,FD_ZERO*/
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../DS/genericDll.h"
#include "../DS/list_functions.h"
#include "../DS/list_Itr.h"

// #define SERVER_IP "10.0.2.15"
#define SERVER_PORT 55555
#define BUFFER_SIZE 4096
#define AWAITING_CLIENTS 10 /*limit max server accept to avoid overload*/
#define MAX_FD 1024
#define FAIL -1
#define MESSAGE_SENT 1
#define NO_MESSAGE -1
/**************************************************************************************/
typedef void (*NewClient)();
typedef void (*GotMsg)(int cliendId, char* buffer, int messageSize);
typedef void (*CloseClient)(int sock);
typedef void (*Fail)();
typedef void (*StopRun)(int stopRun);

typedef struct Server Server;

struct Server
{
    List* m_clients;
    NewClient m_newClientFunc;
    GotMsg m_gotMsgFunc;
    CloseClient m_closeClientFunc;
    Fail m_failFunc;
    StopRun m_stopRunFunc;
    fd_set m_masterfd;
    int m_maxClients;
    int m_sockListen;
    int m_numOfClients;
    
};
/*************************INNER FUNCTIONS*********************************************/
static void Unblock_Sock(int* _sock);
static int InitialServer(Server* server);
static void AcceptCLients(Server* server, int* client_sock);
static int CheckCurrentClient(Server* server, int clientSock);
static void DestroyClient(void* _element);
/**************************SERVER CREATE***********************************************/
Server* ServerCreate(NewClient newClientFunc, GotMsg gotMsgFunc, CloseClient closeClientFunc, Fail failFunc,StopRun stopRunFunc, int maxClients)
{
    Server* server = NULL;
    List* clients = NULL;

    if(gotMsgFunc == NULL || failFunc == NULL || maxClients <= 0 || maxClients > 1000)
    {
        return NULL;
    }
    clients = ListCreate();
    if(NULL == clients) 
    {
        return NULL;
    }
    server = (Server*)malloc(sizeof(Server));
    if(NULL == server)
    {
        return NULL;
    }
    server->m_clients = clients;
    server->m_newClientFunc = newClientFunc;
    server->m_gotMsgFunc = gotMsgFunc;
    server->m_closeClientFunc = closeClientFunc;
    server->m_failFunc = failFunc;
    server->m_stopRunFunc = stopRunFunc;
    server->m_numOfClients = 0;
    server->m_maxClients = maxClients;
    server->m_sockListen = InitialServer(server); /*build a function*/
    
    if(server->m_sockListen == FAIL)
    {
        if(server->m_failFunc)
        {
            server->m_failFunc();
        }
        ListDestroy(&clients, NULL);
        free(server);
        return NULL;
    }
    FD_ZERO(&server->m_masterfd);
    FD_SET(server->m_sockListen, &server->m_masterfd);

    return server;
}
/**************************************************************************************/
static void Unblock_Sock(int* _sock)
{
    int flags;
    if (FAIL == (flags = fcntl(*_sock, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return;
    }
    if(fcntl(*_sock, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
        return;
    }
}
/**************************************************************************************/
static int InitialServer(Server* server)
{
    struct sockaddr_in sin;    
    int optval = 1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket func failure\n");
        return FAIL;
    }
    Unblock_Sock(&sock);
     if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return FAIL;
    }
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("binding failed\n");
        return FAIL;
    }
    if (listen(sock, server->m_maxClients) < 0)
    {
        perror("listen failed\n");
        return FAIL;
    }

    return sock;
}
/**************************************************************************************/
static void AcceptCLients(Server* server, int* client_sock)
{
    struct sockaddr_in client_sin;
    int addr_len = sizeof(client_sin);
    int* curClient;
    int index;
    for(index = 0; index < AWAITING_CLIENTS; index++)
    {
        *client_sock = accept(server->m_sockListen, (struct sockaddr *) &client_sin, &addr_len);
        if (*client_sock > 0)
        {
            if(server->m_numOfClients >= server->m_maxClients)
            {
                close(*client_sock);
                if(server->m_closeClientFunc)
                {
                    server->m_closeClientFunc(*client_sock);
                }
            }
            else
            {
                curClient = (int*)malloc(sizeof(int));
                *curClient = *client_sock;
                ListPushHead(server->m_clients, curClient);
                FD_SET(*client_sock, &server->m_masterfd);
                server->m_numOfClients++;
                if(server->m_newClientFunc)
                {
                    server->m_newClientFunc();
                }
            }
        }
    }
}
/*******************************SERVER RUN*********************************************/
Server* ServerRun(Server* server)
{
    ListItr current, end, itrCur;
    int* curClient = NULL, *deleteClient = NULL;
    int client_sock;
    int index, curClientSock, activity;
    fd_set masterfd, tempfd;

    while(server->m_stopRunFunc)
    {
        tempfd = server->m_masterfd;
        activity = select(MAX_FD, &tempfd ,NULL, NULL, NULL);
        if(activity < 0 && errno != EINTR)
        {
            break;
        }
        if(activity > 0 && FD_ISSET(server->m_sockListen, &tempfd))
        {
            AcceptCLients(server, &client_sock);
            activity--;
        }
        current = ListItr_Begin(server->m_clients);
        end = ListItr_End(server->m_clients);
    
        while(activity > 0 && current != end)
        {
            curClientSock = *(int*)ListItr_Get(current);
            current = ListItr_Next(current);
            if(FD_ISSET(curClientSock, &tempfd))
            {
                if(CheckCurrentClient(server, curClientSock) == NO_MESSAGE)
                {
                    server->m_numOfClients--;;
                    close(curClientSock);
                    FD_CLR(curClientSock, &server->m_masterfd);
                    itrCur = ListItr_Prev(current);
                    deleteClient = (int*)ListItr_Remove(itrCur);                  
                    free(deleteClient);/*free the client*/
                    if(server->m_closeClientFunc)
                    {
                        server->m_closeClientFunc(curClientSock);
                    }
                }
                
                activity--;
            }
        }
    }
}
/**********************SERVER SEND MESSAGE*******************************************/
void ServerSendMessage(Server* server, int clientSock, int* message, int messageSize)
{
    int send_bytes;
    send_bytes = send(clientSock, message, messageSize, 0); 
    if (send_bytes < 0 && server->m_failFunc) 
    {
        server->m_failFunc();
    }
}
/**************************************************************************************/
static int CheckCurrentClient(Server* server, int clientSock)
{
    char buffer[BUFFER_SIZE];
    int read_bytes;
    read_bytes = recv(clientSock, buffer, sizeof(buffer), 0);
    if (read_bytes == 0)
    {     
        return NO_MESSAGE;
    } 
    else if (read_bytes < 0) 
    { 
        perror("recv failed\n");
        return FAIL;
    }
    else
    {    
        server->m_gotMsgFunc(clientSock, buffer, read_bytes); 
    }

    return MESSAGE_SENT;

}
/**************************************************************************************/
static void DestroyClient(void* _element)
{
    if((int*)_element)
    {
        close(*(int*)_element);
        free(_element);
    }
}
/**************************************************************************************/
void ServerDestroy(Server** server)
{
    if(server && *server)
    {
        ListDestroy(&(*server)->m_clients, DestroyClient);
        close((*server)->m_sockListen);
        free(*server);
        *server = NULL;
    }
}
