#include <stdio.h>
#include <string.h>
#include "serverNet.h"

void gotMsg(int clientID, char* message, int size)
{
    Server* server;
    char* buffer = "hello server";
    ServerSendMessage(server, clientID, buffer, strlen(buffer));
}

void fail(Server* server, int error)
{
    printf("Got an error");
}
/*void ServerStop(int stop)
{
    return;
}*/


int main()
{
    Server* server;
    server = ServerCreate(NULL, gotMsg, NULL, fail, NULL, 10);
    ServerRun(server);      
    return 0;
}