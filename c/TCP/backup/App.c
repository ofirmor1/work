#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serverNet.h"

typedef void (*NewClient)();
typedef void (*GotMsg)(int cliendId, char* buffer, int messageSize);
typedef void (*CloseClient)(int sock);
typedef void (*Fail)();
typedef void (*StopRun)(int stopRun);

int main()
{
    Server* server;
    struct sockaddr_in sin;
    char buffer[BUFFER_SIZE];
    char* clientMsg = "Hello server ";
    char* serverMsg;
    int send_bytes, read_bytes;
    int expected_data_len = sizeof(buffer);
    int optval = 1;
    int data_len = DATA_LEN;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        perror("socket() failed");
        return;
    }
    memset(&sin, 0 ,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(SERVER_PORT);

    ServerCreate((*NewClient)(), (*GotMsg)(sock, &clientMsg, strlen(clientMsg)), (*CloseClient)(sock), NULL, 1, 10);
    Server* ServerRun(server);
    send_bytes = send(sock, (const char*)massage, data_len, 0);
    if(send_bytes < 0)
    {
        perror("send_bytes failed");
    }
    read_bytes = recv(sock, buffer, expected_data_len, 0);
    if(read_bytes < 0 && (errno != EAGAIN && errno != EWOULDBLOCK))
    {
        perror("read_bytes failed");
        close(sock);
        return;
    }
    ServerSendMessage(server, sock, &serverMsg, strlen(message));
    printf("server: %s\n", buffer);
    close(sock);
    ServerDestroy(*server);

    return 0;
}