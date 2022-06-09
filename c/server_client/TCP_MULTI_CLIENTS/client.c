#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
/*#include <sys/un.h>*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SERVER_IP "10.0.2.15"
#define SERVER_PORT 55555
#define MASSAGE_LEN 10
#define NUM_MASSAGES 50
#define BUFFER_SIZE 200

/***********************Initialization: server + client, socket*******************************/
static int InitialClient()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        perror("socket() failed");
        abort();
    }

    return sock;

/******************************Connection Establishment***************************************/

    struct sockaddr_in sin;
    memset(&sin, 0 ,sizeof(sin));

    sin.sin_family    = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(SERVER_PORT);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
    {
        perror(“connection failed”);
        abort();
    }
}

int main()
{
    int sock = InitialClient();
    char *data_addr = "hello, world";
    int data_len = strlen(&data_addr);
    ServerSendMessage(data_addr, data_len, sock);
    
}


