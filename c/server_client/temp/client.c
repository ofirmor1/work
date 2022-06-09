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

void ServerSendMassage(int clientSock , char* data, int data_len)
{
    int sent_bytes;

    sent_bytes = sendto(clientSock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0)
    {
        perror("sendto failed");
        abort();
    }
}

void ServerRecieveMassage(int clientSock , char* buffer, int data_len)
{
    int read_bytes;

    read_bytes = recvfrom(clientSock, buffer, sizeof(buffer), 0, (struct sockaddr *) &sin, &sin_len);
    if (read_bytes < 0)
    {
        perror("recvfrom failed");
        abort();
    }
}

int main()
{
    int sock, length;
    char buffer[1024] = "Hello Server";
    length = strlen(buffer);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    ServerRecieveMassage(sock, buffer, length)
    ServerSendMassage(sock, buffer, length);
}
