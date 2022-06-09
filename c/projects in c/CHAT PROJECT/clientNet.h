#ifndef __CLIENT_NET_H__
#define __CLIENT_NET_H__

#define ERROR -1
#define MESSAGE_LEN 50

/*********************************************************/

/**
 * @brief create socket to server and connect to server
 * 
 * @param _ip char pointer of ip address
 * @param _port int port - same for all clients
 * @return on success - return socket to server, ERROR - on fail
 */
int ClientInit(char* _ip, int _port);
/*********************************************************/

/**
 * @brief send message to server
 * 
 * @param _serverSock int socket of server
 * @param _buffer char pointer of buffer
 * @return int SUCCESS on seccess, ERROR - on fail
 */
int ClientNet_SendMsg(int _serverSock, char* _buffer, int len);
/*********************************************************/

/**
 * @brief recieve message from server
 * 
 * @param _serverSock int socket of server
 * @param _buffer char pointer of buffer
 * @return int SUCCESS on seccess, ERROR - on fail
 */
int ClientNet_RcvMsg(int _serverSock, char* _buffer);
/*********************************************************/

/**
 * @brief close socket of server
 * 
 * @param _serverSock int socket of server
 * @return None(void)
 */
int ClientNet_Close(int _serverSock);

#endif /*ifndef __CLIENT_NET_H__*/

