#include "tcp_net.hpp"

#include <cpprest/uri.h>

#define BUFFER_SIZE 4096

namespace cdr
{

TCPNet::TCPNet(const char* a_ip , int a_port, BillingInfo a_bi)
: m_server(a_bi)
, m_ip(a_ip)
, m_port(a_port)
{
    int optval = 1;
    FD_ZERO(&m_master);
    FD_ZERO(&m_temp);
    struct sockaddr_in sin;
    m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_listeningSocket < 0)
    {
        throw "socket failed";
    }
    FD_SET(m_listeningSocket, &m_master);
    if (setsockopt(m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        throw "reuse failed";
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);
    if (bind(m_listeningSocket, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        throw "bind failed";
    }
    if (listen(m_listeningSocket, 32) < 0){
        throw "listen failed";
    }
}

TCPNet::~TCPNet()
{
    close(m_listeningSocket);
}

int TCPNet::acceptConnection()
{
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(m_listeningSocket, (struct sockaddr *)&client_sin, &addr_len);
    return client_sock;
}

void TCPNet::checkNewClients()
{
    int client_sock = acceptConnection();
    if (client_sock < 0)
    {
        throw "error at accept";
    }
    FD_SET(client_sock, &m_master);
    m_socketList.push_back(client_sock);
}

void TCPNet::checkCurClients(int& a_activity)
{
    if (m_socketList.empty())
    {
        return;
    }
    checkClient(a_activity);
}

void TCPNet::checkClient(int& a_activity)
{
    auto it = m_socketList.begin();
    while (it != m_socketList.end() && a_activity > 0)
    {
        if (FD_ISSET(*it, &m_temp) == 0)
        {
            ++it;
            continue;
        }
        char buffer[BUFFER_SIZE];
        int readBytes;
        int dataLen = sizeof(buffer);
        readBytes = recv(*it, buffer, dataLen, 0);
        if (readBytes < 0)
        {
            throw "recv failed";
        }
        else if (readBytes == 0)
        {
            m_socketList.erase(it++);
            FD_CLR(*it, &m_master);
            close(*it);
            a_activity--;
        }
        else
        {
            buffer[readBytes] = '\0';
            json j = json::parse(buffer);
            ReqHandle reqH(m_ip, m_port);
            json response = m_server.getMsg(reqH);
            sendData(response.dump().c_str(), *it);
            a_activity--;
        }
        ++it;
    }
}

void TCPNet::sendData(const char* a_data, int a_socket)
{
    int sendBytes, dataLen;
    dataLen = strlen(a_data);
    sendBytes = send(a_socket, a_data, dataLen, 0);
    if (sendBytes < 0)
    {
        throw "send failed";
    }
}

void TCPNet::runServer()
{
    int activity;
    while (1)
    {
        m_temp = m_master;
        activity = select(1024, &m_temp, NULL, NULL, NULL);
        if (FD_ISSET(m_listeningSocket, &m_temp) > 0)
        {
            checkNewClients();
            if (activity == 1)
            {
                continue;
            }
            activity--;
        }
        checkCurClients(activity);
    } 
}


}//namespace cdr