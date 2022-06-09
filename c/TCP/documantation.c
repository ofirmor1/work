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
int sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
    perror(“socket() failed”);
    abort();
}
/*******************************Reusing the same port*****************************************/
int optval = 1;
if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror(“reuse failed”);
    abort();
}
/****************************Initialization: server, bind()***********************************/
struct sockaddr_in sin;
memset(&sin, 0, sizeof(sin));
sin.sin_family = AF_INET;
sin.sin_addr.s_addr = INADDR_ANY;
sin.sin_port = htons(server_port);

if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    perror(“bind failed”);
    abort();
}
/***************************Initialization: server, listen()************************************/
if (listen(sock, back_log) < 0) {
    perror(“listen failed”);
    abort();
}
/***************************Connection Establishment - client***********************************/

struct sockaddr_in sin;
memset(&sin, 0 ,sizeof(sin));

sin.sin_family    = AF_INET;
sin.sin_addr.s_addr = inet_addr(“128.32.132.214”);
sin.sin_port = htons(80);

if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
    perror(“connection failed”);
    abort();
}

/***************************Connection Establishment - server***********************************/

struct sockaddr_in client_sin;
int addr_len = sizeof(client_sin);
int client_sock = accept(listening_sock, 
                        (struct sockaddr *) &client_sin,
                        &addr_len);
if (client_sock < 0) {
    perror(“accept failed”);
    abort();
}

/***************************Sending Data***********************************/
char *data_addr = “hello, world”;
int data_len = 12;

int sent_bytes = send(sock, data_addr, data_len, 0); 
if (sent_bytes < 0) {
    perror(“send failed”);
}
/***************************Receiving Data***********************************/
char buffer[4096];
int expected_data_len = sizeof(buffer);
int read_bytes = recv(sock, buffer, expected_data_len, 0);
if (read_bytes == 0) {     // connection is closed
     …
} else if (read_bytes < 0) { // error
    perror(“recv failed”);
} else {    // OK. But no guarantee read_bytes == expected_data_len
    …
}

/***************************Termination***********************************/
/*after use the socket*/
close(sock);






