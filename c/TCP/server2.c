#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h> /*FD_SET,FD_ZERO*/
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
/*#include <sys/un.h>*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../DS/genericDll.h"
#include "../DS/list_functions.h"
#include "../DS/list_Itr.h"

// #define SERVER_IP "10.0.2.15"
#define SERVER_PORT 55555
#define BUFFER_SIZE 4096
#define MAX_CLIENTS 1000 /*limit max server accept to avoid overload*/
#define MAX_FD 1024
#define FAIL -1
#define MESSAGE_SENT 1
#define NO_MESSAGE -1


/**************************************************************************************/
void Unblock_Sock(int* _sock)
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
void AcceptCLients(List* clientsList,int sock, int* client_sock, int* numOfClients, fd_set* masterfd)
{
    struct sockaddr_in client_sin;
    int addr_len = sizeof(client_sin);
    int* curClient;
    int index;
    for(index = 0; index < MAX_CLIENTS; index++)
    {
        *client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (*client_sock > 0)
        {
            curClient = (int*)malloc(sizeof(int));
            *curClient = *client_sock;
            ListPushHead(clientsList, curClient);
            FD_SET(*client_sock, masterfd);
            (*numOfClients)--;
        }
    }
}
/**************************************************************************************/
void DestroyClient(void* _element)
{
    if((int*)_element)
    {
        close(*(int*)_element);
        free(_element);
    }
}
/**************************************************************************************/
int CheckCurrentClient(int _clientSock)
{
    char buffer[BUFFER_SIZE];
    int send_bytes, read_bytes;
    char* message = "Got your message";

    read_bytes = recv(_clientSock, buffer, sizeof(buffer), 0);
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
        printf("client: %s\n", buffer);
        send_bytes = send(_clientSock, message, strlen(message), 0); 
        if (send_bytes < 0) 
        {
            perror("send failed\n");
        }
    }

    return MESSAGE_SENT;
}
/**************************************************************************************/
int InitialServer()
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
    if (listen(sock, MAX_CLIENTS) < 0)
    {
        perror("listen failed\n");
        return FAIL;
    }

    return sock;
}
/**************************************************************************************/
void TCPServer()
{
    List* clientsList;
    ListItr current, end, itrCur;
    char buffer[4096];
    int* curClient = NULL, *deleteClient = NULL;
    int master_socket, client_sock;
    int index, curClientSock, activity;
    int numOfClients = 0;
    fd_set masterfd, tempfd;

    clientsList = ListCreate();
    master_socket = InitialServer();
    if(master_socket == FAIL)
    {
        perror("socket func failure\n");
        return;
    }
    FD_ZERO(&masterfd);
    FD_SET(master_socket, &masterfd);
    while(1)
    {
        tempfd = masterfd;
        activity = select(MAX_FD, &tempfd ,NULL, NULL, NULL);
        if(activity < 0 && errno != EINTR)
        {
            perror("select error");
            break;
        }
        if(activity > 0 && FD_ISSET(master_socket, &tempfd))
        {
            AcceptCLients(clientsList, master_socket, &client_sock, &numOfClients, &masterfd);
            activity--;
        }
        current = ListItr_Begin(clientsList);
        end = ListItr_End(clientsList);
    
        while(activity > 0 && current != end)
        {
            curClientSock = *(int*)ListItr_Get(current);
            current = ListItr_Next(current);
            if(FD_ISSET(curClientSock, &tempfd))
            {
                if(CheckCurrentClient(curClientSock) == NO_MESSAGE)
                {
                    numOfClients--;
                    close(curClientSock);
                    FD_CLR(curClientSock, &masterfd);
                    itrCur = ListItr_Prev(current);
                    deleteClient = (int*)ListItr_Remove(itrCur);                  
                    free(deleteClient);/*free the client*/
                }
                
                activity--;
            }
        }
    }
    close(master_socket);
    ListDestroy(&clientsList, DestroyClient);
}
/**************************************************************************************/
int main()
{
    TCPServer();
    return 0;
}