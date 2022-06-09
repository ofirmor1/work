#include<string>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include "tcp.hpp"

namespace TcpWrapper{

    const int BUFFER_LEN = 1000;
    int TcpSocket::sendMsg(double a_attidue, int a_id, double a_speed, size_t a_len, int a_flags)
    {
        char buffer[BUFFER_LEN];
        int send_bytes, sent_bytes = 0, left_bytes = a_len;
        Message msg;
        msg.altitude = a_attidue;
        msg.id = a_id;
        msg.speed = a_speed;
        memcpy(buffer, &msg , a_len);
        while(sent_bytes < a_len)
        {
            send_bytes = send(m_socket, buffer, a_len, a_flags);
        
            if(send_bytes == -1)
            {
                perror("send_bytes failed");
                break;
            }
            else
            {
                sent_bytes += sent_bytes;
                left_bytes -= sent_bytes;
            }
        }

        return left_bytes;
    }
}