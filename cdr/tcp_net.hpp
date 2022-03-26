#ifndef TCP_NET_HPP
#define TCP_NET_HPP

#include <iostream>
#include <string.h>    /*for memset*/
#include <unistd.h>    /*for fcntl*/
#include <fcntl.h>     /*for fcntl*/
#include <sys/types.h> /* for socket */
#include <sys/socket.h>/* for socket */
#include <netinet/in.h>/* for socket */
#include <sys/select.h>/*for FD_SET*/
#include <sys/time.h>  /*for FD_SET*/
#include <exception>
#include <list>
#include <sstream>
#include <queue>
#include "json.hpp"
#include "tcp_server.hpp"
#include "requests_handle.hpp"

namespace cdr
{
using json = nlohmann::json;
using string = std::string;

class TCPNet
{
public:
    TCPNet(const char* a_ip , int a_port, BillingInfo a_bi);
    ~TCPNet();

    void runServer();

    void sendData(const char* a_data, int a_socket);

private:
    void checkNewClients();
    int acceptConnection();
    void checkCurClients(int& a_activity);
    void checkClient(int& a_activity);

private:
    TCPServer m_server;
    const char* m_ip;
    int m_port;
    int m_listeningSocket;
    fd_set m_master;
    fd_set m_temp;
    std::list<int> m_socketList;
    
};

}//namespace cdr

#endif /*#ifndef TCP_NET_HPP*/