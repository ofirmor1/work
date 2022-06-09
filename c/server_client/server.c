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
#define MASSAGE_LEN 50
#define NUM_MASSAGES 5
#define BUFFER_SIZE 1000

int main()
{
    int sent_bytes, read_bytes, sock, index;
    struct sockaddr_in sin;
    struct sockaddr_in6 sin6;
    socklen_t sinLength;
    char massage[NUM_MASSAGES][MASSAGE_LEN] = {"\n\nHello Client\n", "\nmassage 1\n", "\nmassage 2\n", "\nmassage 3\n", "\nmassage 4\n"};
    char buffer[BUFFER_SIZE];

    printf("/***************IPv4 Addr*******************/");
    
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(SERVER_IP);
    sin.sin_port = htons(SERVER_PORT);
    sinLength = sizeof(sin);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();                
    } 
    if(bind(sock, (struct sockaddr*) &sin, sizeof(sin)) < 0)
    {
        perror("bind failed");
        abort();        
    }
    for(index = 0; index < 5; index++)
    {
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&sin, &sinLength);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            abort();
        }
        sent_bytes = sendto(sock, massage[index], strlen(massage[index]), 0, (struct sockaddr *)&sin, sizeof(sin));
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            abort();
        }
        sleep(1.5);
        printf("%s", buffer);
    } 

    close(sock);

/*****************************************************************************************************/
   
    printf("\n\n/***************IPv6 Addr*******************/\n");

    memset(&sin6, 0, sizeof(sin6));
    sin6.sin6_family = AF_INET6;
    sin6.sin6_addr = in6addr_loopback;
    sin6.sin6_port = htons(SERVER_PORT);
    sinLength = sizeof(sin6);
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket failed");
        abort();                
    } 
    if(bind(sock, (struct sockaddr*) &sin6, sizeof(sin6)) < 0)
    {
        perror("bind failed");
        abort();        
    }
    for(index = 0; index < 5; index++)
    {
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*) &sin6, &sinLength);
        if (read_bytes < 0)
        {
            perror("recvfrom failed");
            abort();
        }
        sent_bytes = sendto(sock, massage[index], strlen(massage[index]), 0, (struct sockaddr*) &sin6, sizeof(sin6));
        if (sent_bytes < 0)
        {
            perror("sendto failed");
            abort();
        }
        sleep(1.5);
        printf("%s", buffer);
    } 

    close(sock);
       
}