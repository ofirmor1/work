#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "clientNet.h"
#include "Chat.h"

int ClientInit(char* _ip, int _port)
{
    struct sockaddr_in sin;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        perror("socket() failed");
        return ERROR;
    }
    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(_ip);
    sin.sin_port = htons(_port);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
    {
        perror("connection to server has failed");
        return ERROR;
    }   

    return sock;
}

int ClientNet_SendMsg(int _serverSock, char* _buffer, int len)
{   
    int send_bytes;
    send_bytes = send(_serverSock, _buffer, len, 0);
    if(send_bytes < 0)
    {
        perror("send_bytes failed");
        return ERROR;
    }

    return SUCCESS;
}

int ClientNet_RcvMsg(int _serverSock, char* _buffer)
{
    int read_bytes;
    read_bytes = recv(_serverSock, _buffer, MESSAGE_LEN, 0);
    if(read_bytes < 0)
    {
        perror("read_bytes failed");
        return ERROR;
    }

    return SUCCESS;
}

int ClientNet_Close(int _serverSock)
{
    close(_serverSock);
    return SUCCESS;
}



