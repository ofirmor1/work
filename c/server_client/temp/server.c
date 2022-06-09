#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>
/*#include <sys/un.h>*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TARGET_ADDR 127.0.0.1
#define TARGET_PORT 55555

void ServerSendMassage(int clientSock, char *buffer, int data_len)
{
    int sent_bytes;

    sent_bytes = sendto(clientSock, buffer, data_len, 0, (struct sockaddr *)&sin, sizeof(sin));
    if (sent_bytes < 0)
    {
        perror("sendto failed");
        abort();
    }
}

void ServerRecieveMassage(int clientSock, char *buffer, int data_len)
{
    int read_bytes;
    struct sockaddr_in sin;
    struct sockaddr_in sin_len;
    read_bytes = recvfrom(clientSock, buffer, sizeof(buffer), 0, (struct sockaddr *)&sin, &sin_len);
    if (read_bytes < 0)
    {
        perror("recvfrom failed");
        abort();
    }
}

void ServerBind(int clientSock, char *buffer, int data_len)
{
    
    struct sockaddr_in sin;
    struct sockaddr_in sin_len;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("TARGET_ADDR");
    sin.sin_port = htons("TARGET_PORT");

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind failed");
        abort();
    }
}

int main()
{
    int sock, length;
    char buffer[1024] = "Hello Client";
    length = strlen(buffer);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();
    }
    ServerBind(sock, buffer, length);
    ServerRecieveMassage(sock, buffer, length)
    ServerSendMassage(sock, buffer, length);
}
