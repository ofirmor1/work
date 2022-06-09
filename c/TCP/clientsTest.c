#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
/*#include <sys/un.h>*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SERVER_PORT 55555
#define ARRAY_SIZE 100
#define BUFFER_SIZE 10000
#define DISCONNECT -1
#define DATA_LEN 50

void TCPClient()
{
	struct sockaddr_in sin;
    char buffer[BUFFER_SIZE];
    char massage[DATA_LEN] = "new message";
	char str[30];
    int send_bytes, read_bytes;
    int expected_data_len = sizeof(buffer);
    int optval = 1;
    int data_len = DATA_LEN;
    int sock, index, randNum, count = 100000;
	int* arr;

    arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
	memset(arr, -1, sizeof(int)*ARRAY_SIZE);
	srand(time(NULL));
	while(count > 0)
	{
		for(index = 0; index < ARRAY_SIZE; index++)
		{
			count--;
			randNum = rand() % 100;
			if(arr[index] < 0) /*if disconnect*/
			{
				if(randNum < 30)
				{	
					sock = socket(AF_INET, SOCK_STREAM, 0);
					if(sock < 0)
					{
						perror("socket() failed");
						continue;
					}
					memset(&sin, 0, sizeof(sin));
					sin.sin_family = AF_INET;
					sin.sin_addr.s_addr = inet_addr("127.0.0.1");
					sin.sin_port = htons(SERVER_PORT);
					if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) 
					{
						perror("connection to server has failed");
						continue;
					}
					
					arr[index] = sock;
				}
			}
			
			else /*if connect*/
			{
				if (randNum < 5)
				{
					close(arr[index]);
					arr[index] = DISCONNECT;
				}
				else if (randNum > 70)
				{
					printf("socket: %d client index: %d ", arr[index], index);
					
					send_bytes = send(arr[index], massage, strlen(massage), 0);
					if(send_bytes < 0)
					{
						perror("send_bytes failed");
						continue;
					}
					read_bytes = recv(arr[index], buffer, expected_data_len, 0);
					if (read_bytes < 0)
					{
						perror("read_bytes failed\n");
						arr[index] = DISCONNECT;
					}
					else if(read_bytes == 0)
					{
						close(arr[index]);
						arr[index] = DISCONNECT;
					}
					else if(read_bytes > 0)
					{
						printf("\tmessage from server: %s\n", buffer);
					}  
				}
			}
		}
	}

    for (index = 0; index < ARRAY_SIZE; index++)
    {
        close(arr[index]);
        arr[index] = DISCONNECT;
    }
    free(arr);
}

int main()
{
    TCPClient();
    return 0;
}
