#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <list>
#include <unistd.h>

#include "protocol.hpp"
#include "event.hpp"
#include "blocking_queue.hpp"
#include "thread.hpp"
#include "log.hpp"

namespace home
{

class TcpServer
{
public: 
    TcpServer(const char* a_serverIp, int a_servrPort, home::BlockingQueue<home::Event>& a_queue, home::Log& a_log);
    ~TcpServer();

    void runServer();
    void stop();

private:    
    void acceptNewClient();
    void takeCareExistsClients();
    bool receiveData(int a_clientSocket);
    void closeClientSockets();

    TcpServer(TcpServer const& a_source);
    TcpServer& operator=(TcpServer const& a_source);

private:
    int m_listenSocket;
    int m_stopSocket;
    struct sockaddr_in m_sin;
    struct sockaddr_in m_clientSin;
    fd_set m_socketsList;
    fd_set m_activeSockets;
    int m_clientsCountr;
    int m_activity;
    unsigned char m_buffer[1000];
    bool m_stop;
    std::list<int> m_clientSockets;
    home::BlockingQueue<home::Event>& m_queue;
    home::Thread* m_thread;
    home::Log& m_log;
};


}//namespace home

#endif // TCP_SERVER_HPP