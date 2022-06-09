#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
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
#define BUFFER_SIZE 100
#define NUM_OF_CLIENTS 3
#define BACK_LOG 100 
#define FAIL -1

/**************************************************************************************/
void Unblock_Sock(int* _sock)
{
    int flags;
    if (FAIL == (flags = fcntl(*_sock, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return;
    }
    if(FAIL == fcntl(*_sock, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
        return;
    }
}

void DestroyFunc(void* _element)
{
    if((int*)_element)
    {
        close(*(int*)_element);
        free(_element);
    }
}
/**************************************************************************************/
int MangeDataFlow(ListItr curClient, ListItr end, int* numOfClients)
{
    ListItr itr;
    char buffer[4096];
    void* data;
    int  send_bytes, read_bytes;
    int expected_data_len = sizeof(buffer);
    char* massage = "Got your massage client";

    while(curClient != end)
    {
        data = ListItr_Get(curClient);
        buffer[BUFFER_SIZE];
        
        read_bytes = recv(*(int*)data, buffer, expected_data_len, 0);
        if (read_bytes == 0)
        {     
            itr = curClient;
            curClient = ListItr_Next(curClient);
            close(*(int*)data);
            (*numOfClients)++;
            free(ListItr_Remove(itr));
        } 
        else if (read_bytes < 0) 
        { 
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                perror("recv failed\n");
                itr = curClient;
                curClient = ListItr_Next(curClient);
                close(*(int*)data);
                (*numOfClients)++;
                free(ListItr_Remove(itr));
            }
            else
            {
                curClient = ListItr_Next(curClient);
            }
        }
        else if (read_bytes > 0)
        {
            buffer[read_bytes] = '\0';
            printf("client: %s\n", buffer);
            send_bytes = send(*(int*)data, (const char*)massage, strlen(massage), 0); 
            if (send_bytes < 0 && (errno != EAGAIN && errno != EWOULDBLOCK)) 
            {
                perror("send failed");

            }
            curClient = ListItr_Next(curClient);
        }
    }
}
/**************************************************************************************/
void TCPServer()
{
    List* ClientsList;
    ListItr begin, end;
    struct sockaddr_in sin;
    struct sockaddr_in client_sin;
    char buffer[4096];
    int addr_len = sizeof(client_sin);
    int* curClient;
    int client_sock, optval = 1;
    int numOfClients = NUM_OF_CLIENTS;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    ClientsList = ListCreate();
    if (sock < 0)
    {
        perror("socket func failure\n");
        return;
    }
    Unblock_Sock(&sock);
     if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return;
    }
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("binding failed\n");
        return;
    }
    if (listen(sock, BACK_LOG) < 0)
    {
        perror("listen failed\n");
        return;
    }
    while(1)
    {
        client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0  && ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
        {
            perror("accept failed");
            break;
        }
        else if (client_sock > 0)
        {
            Unblock_Sock(&client_sock);
            curClient = (int*)malloc(sizeof(int));
            *curClient = client_sock;
            ListPushHead(ClientsList, curClient);
            numOfClients--;
        }
        begin = ListItr_Begin(ClientsList);
        end = ListItr_End(ClientsList);
        MangeDataFlow(begin, end, &numOfClients);
    }
    close(sock);
    ListDestroy(&ClientsList, DestroyFunc);
}
/**************************************************************************************/
int main()
{
    TCPServer();
    return 0;
}