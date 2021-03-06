#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MSG_LEN 600
#define PORT 12345

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    char* ip = argv[1];
    char* username = argv[2];  
    char* groupName = argv[3];
    char msg[MSG_LEN];
    char message[MSG_LEN*2];
    int pid, nbytes, fd;
    FILE* f2 = fopen("pidC.txt","w");
    pid = getpid();
    fprintf(f2,"%d",pid);
    fclose(f2);
    switch (argc)
    {
    case 1:
        strcpy(ip, argv[1]);
    case 2:
        strcpy(username, argv[2]);
    case 3:
        strcpy(groupName, argv[3]);
        break;
    default:
        break;
    }
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) 
    {
        perror("socket() failed");
        return 1;
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(PORT);

    printf("Hello %s, you're connected to %s group. type your message. \n", username, groupName);
    while (1) 
    {
        fgets(msg, MSG_LEN, stdin);
        sprintf(message, "\033[1;32m%s\033[0m : %s", username, msg);
        nbytes = sendto(fd, message, strlen(message), 0, (struct sockaddr*) &addr, sizeof(addr));
        if (nbytes < 0) 
        {
            sleep(5);
            perror("sendto failed");
            return 1;
        }
    }

    return 0;
}
