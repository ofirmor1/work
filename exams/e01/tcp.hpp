#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <stddef.h>
namespace TcpWrapper{

typedef struct Message Message;
struct Message{
 int id;
 double speed;
 double altitude;
};

class TcpSocket
{
public:
    TcpSocket();
    TcpSocket(int a_socket, bool a_isConnected, bool a_isBound);

    ~TcpSocket();
    TcpSocket(TcpSocket const& a_socket);
    TcpSocket& operator=(TcpSocket const& a_socket);

    void connect(char* a_addr, int port);
    int sendMsg(double a_attidue, int a_id, double a_speed, size_t a_len, int a_flags);
    void recieveMsg(char* a_msg, size_t a_len, int a_len);

private:
    int m_socket;
    bool m_isConnected;
    bool m_isClosed;
    bool m_isBound;
};

}




#endif /*TCP_SOCKET_H*/

