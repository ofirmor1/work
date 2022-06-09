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

int main()
{
    int sent_bytes, read_bytes, sock, index;
    struct sockaddr_in server;
    struct sockaddr_in6 server6;
    socklen_t sinLength;
    char massage[NUM_MASSAGES][MASSAGE_LEN] = {"\n\nHello Server\n", "\nmassage 1\n", "\nmassage 2\n", "\nmassage 3\n", "\nmassage 4\n"};
    char buffer[BUFFER_SIZE];
    char str[INET6_ADDRSTRLEN];

    printf("/***************IPv4 Addr*******************/");
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);
    sinLength = sizeof(server);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();                
    } 
    for(index = 0; index < 5; index++)
    {
        sent_bytes = sendto(sock, massage[index], strlen(massage[index]), 0, (struct sockaddr *)&server, sizeof(server));
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            abort();
        }
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, &sinLength);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            abort();
        }
        sleep(1.5); 
        printf("%s", buffer);
    } 

    close(sock);

/*****************************************************************************************************/

    printf("/***************IPv6 Addr*******************/");

    memset(&server6, 0, sizeof(server6));
    server6.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "fe80::311d:e09d:3e18:2bdf", &(server6.sin6_addr));
    server6.sin6_port = htons(SERVER_PORT);
    sinLength = sizeof(server6);
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();                
    } 
    for(index = 0; index < 5; index++)
    {
        sent_bytes = sendto(sock, massage[index], strlen(massage[index]), 0, (struct sockaddr*)&server6, sizeof(server6));
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            abort();
        }
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&server6, &sinLength);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            abort();
        }
        sleep(2); 
        printf("%s", buffer);
    } 

    close(sock);
     
}