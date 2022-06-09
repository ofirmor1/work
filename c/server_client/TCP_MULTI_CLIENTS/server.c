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
#define SERVER_PORT 45897
#define MASSAGE_LEN 100
#define NUM_MASSAGES 50
#define BUFFER_SIZE 4096
#define FAILED -1
#define BACK_LOG 1


static int InitialServer()
{
    struct sockaddr_in sin;
    int optval = 1;
 /***********************Initialization: server, socket**************************************/   
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("socket func failure\n");
        return FAILED;
    }
/*******************************Reusing the same port*****************************************/
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return FAILED;
    }
 /****************************Initialization: server, bind()***********************************/   
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("binding failed\n");
        return FAILED;
    }
/***************************Initialization: server, listen()************************************/
    if (listen(sock, BACK_LOG) < 0)
    {
        perror("listen failed\n");
        return FAILED;
    }

    return sock;
}
/***************************Connection Establishment - server***********************************/
void Connection(char* data_addr, int size, int sock)
{
    struct sockaddr_in client_sin;
    int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) 
    {
        perror("accept failed");
        abort();
    }
}

/***************************Sending Data***********************************/

void ServerSendMessage(char* massage, int massageSize, int sock)
{
    int sent_bytes = send(sock, massage, massageSize, 0); 
    if (sent_bytes < 0) 
    {
        perror("send failed");
        return;
    }
}

/***************************Receiving Data***********************************/
void ServerRecieveMessage(char* massage, int massageSize, int sock)
{
    char buffer[BUFFER_SIZE];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) 
    {     
        close(sock);
        return;
    } 
    else if (read_bytes < 0) 
    { 
        perror("recv failed\n");
        return;
    } 
    // OK. But no guarantee read_bytes == expected_data_len
    sleep(1.5);
    printf("%s", buffer);
}


int main()
{
    int sock = InitialServer();
    char *data_addr = "hello, world";
    int data_len = strlen(data_addr);
    InitialServer();
    Connection(data_addr, data_len, sock);
    ServerSendMessage(data_addr, data_len, sock);
    ServerRecieveMessage(data_addr, data_len, sock);
    close(sock);
}