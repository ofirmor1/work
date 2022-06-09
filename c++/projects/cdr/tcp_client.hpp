#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <cstddef>

namespace cdr
{
class TCPClient
{
public:
    TCPClient(const char* a_ip, int a_port);
    ~TCPClient();

    void connectServer();
    void sendData(const char * a_data , size_t a_dataSize);
    char* receiveData(size_t _dataSize);

private:
    const char* m_ip;
    int m_port;
    int m_socket;
    
};

}//namespace cdr

#endif /*TCP_CLIENT_HPP*/