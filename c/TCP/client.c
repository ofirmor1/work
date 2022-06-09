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

// #define SERVER_IP "10.0.2.15"
#define SERVER_PORT 55555
#define DATA_LEN 50
#define BUFFER_SIZE 4096
/**************************************************************************************/
void TCPClient()
{
    struct sockaddr_in sin;
    char buffer[BUFFER_SIZE];
    char* massage = "Hello server ";
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
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
    {
        perror("connection to server has failed");
        return;
    }
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
    
    printf("server: %s\n", buffer);
    close(sock);
    return;
}
/**************************************************************************************/
int main()
{
    TCPClient();

    return 0;
}