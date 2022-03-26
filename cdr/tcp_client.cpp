#include "tcp_client.hpp"

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <sys/types.h> /* for socket */
#include <sys/socket.h>/* for socket */
#include <netinet/in.h>/* for socket */
#include <netinet/in.h>/*for inet_addr*/
#include <arpa/inet.h> /*for inet_addr*/
#include <unistd.h>
#include <string.h>
#include <exception>

#define BUFFER_SIZE 4096

namespace cdr
{
TCPClient::TCPClient(const char* a_ip, int a_port)
: m_ip(a_ip)
, m_port(a_port)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
      throw "Socket Failed";
    }
}

TCPClient::~TCPClient()
{
    close(m_socket);
}

void TCPClient::connectServer()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_ip);
    sin.sin_port = htons(m_port);
    if (connect(m_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        throw "connection failed";
    }
}

void TCPClient::sendData(const char * a_data , size_t a_dataSize)
{
    int send_bytes = send(m_socket, a_data, a_dataSize, 0);
    if (send_bytes < 0)
    {
        throw "send failed";
    }
}

char* TCPClient::receiveData(size_t _dataSize)
{
    char* buffer = new char[BUFFER_SIZE];
    int read_bytes = recv(m_socket, buffer, _dataSize, 0);
    if (read_bytes == 0)
    {
        close(m_socket);
    }
    else if (read_bytes < 0)
    {
        throw "recv failed";
    }
    buffer[read_bytes] = '\0';
    
    return buffer;
}

}//namespace cdr