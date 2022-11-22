#include"server.hpp"

namespace home
{

namespace impel
{

static void* threadFunction(void* arg){
	TcpServer* srv = static_cast<TcpServer*> (arg);
	srv->runServer();
	return 0;
}


} //namespace impel

TcpServer::TcpServer(const char* a_serverIp, int a_servrPort, home::BlockingQueue<home::Event>& a_queue, home::Log& a_log)
: m_listenSocket()
, m_sin()
, m_clientSin()
, m_socketsList()
, m_activeSockets()
, m_clientsCountr(0)
, m_activity()
, m_buffer()
, m_stop(false)
, m_clientSockets()
, m_queue(a_queue)
, m_log(a_log)
{
    //Sin setting
    memset (&m_sin, 0, sizeof(m_sin));	
	m_sin.sin_family = AF_INET;
	m_sin.sin_addr.s_addr =  inet_addr(a_serverIp);
	m_sin.sin_port = htons(a_servrPort);

	//Open listen socket
	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_listenSocket < 0)
	{
		perror("socket fail");
		closeClientSockets();
        throw;
	}

	//Open stop socket
	m_stopSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_stopSocket < 0)
	{
		perror("socket fail");
		closeClientSockets();
        throw;
	}

	//Enter to fd_set for select	
	FD_SET(m_listenSocket, &m_socketsList);
	FD_SET(m_stopSocket, &m_socketsList);	
	
	//Frees listen socket immediately
    int optval = 1;		
	if(setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		perror("setsockopt fail");
		closeClientSockets();
        throw;
	}

	//Set fix ip and port for server		
	if(bind(m_listenSocket, (struct sockaddr*) &m_sin, sizeof(m_sin)) < 0)
	{
        perror("bind fail");
		closeClientSockets();
        throw;
	}
	
	//Set listen socket only for listen	
	if(listen(m_listenSocket, 1000) < 0)
	{
		perror("listen fail");
		closeClientSockets();
        throw;
	}

	m_thread = new home::Thread(impel::threadFunction, this);
}

TcpServer::~TcpServer()
{
	m_thread->join();
	delete m_thread;
}

void TcpServer::runServer()
{
	FD_ZERO(&m_activeSockets);

	while(!m_stop)
	{			
		m_activeSockets = m_socketsList;	
		m_activity = select(1024, &m_activeSockets, 0, 0, 0);
		if((m_activity < 0) && (errno != EINTR))
		{
		    perror("select fail");
			closeClientSockets();
            throw;	
		}

		if(FD_ISSET(m_listenSocket, &m_activeSockets))
		{
			acceptNewClient();
			m_activity--;
		}
		takeCareExistsClients();
	}
}

void TcpServer::acceptNewClient()
{
	socklen_t clientSinLen = sizeof(&m_clientSin);
	int clientSocket = accept(m_listenSocket, (struct sockaddr*)& m_clientSin, &clientSinLen);
	if(clientSocket < 0)
	{
		perror("accept fail");
		closeClientSockets();
        throw;					
	}
	else if (m_clientsCountr < 1000)
	{					
		//Enter to fd_set for select		
		FD_SET(clientSocket, &m_socketsList);	
			
		//Enter socket to list
        m_clientSockets.push_back(clientSocket);			
		++m_clientsCountr;
		return;	
	}
    close(clientSocket);	
}

void TcpServer::takeCareExistsClients()
{
    auto it = m_clientSockets.begin();
    auto end = m_clientSockets.end();
		
	while((it != end) && (m_activity > 0)) 
	{	
        int clientSocket = *it;
		if(FD_ISSET(clientSocket, &m_activeSockets))
		{
			if(receiveData(clientSocket) == false)
			{
				FD_CLR(clientSocket, &m_socketsList);
				close(clientSocket);
				m_clientSockets.erase(it);
				m_clientsCountr--;
			}
			else
			{		
				++it;
			}
			m_activity--;
		}
		else
		{		
			++it;
		}	 
	} 
}

bool TcpServer::receiveData(int a_clientSocket)
{
	unsigned char* bufferPtr = m_buffer;
	int receiveBytes = 0;
	int messageLen = 0;

	do{
		receiveBytes = recv(a_clientSocket, bufferPtr, 1, 0);
		if(receiveBytes == -1)
	  	{
			perror("recv fail");
			return false;
		}
		messageLen = *bufferPtr;
		bufferPtr += receiveBytes;
	}while (receiveBytes != 1);
	
	do{
		receiveBytes = recv(a_clientSocket, bufferPtr, messageLen, 0);
		if(receiveBytes == -1)
	  	{
			perror("recv fail");
			return false;
		}
		messageLen -= receiveBytes;
		bufferPtr += receiveBytes;
	}while (messageLen != 0);
	
	std::string line = home::UnpackLine(m_buffer);
	m_log.writeToFile(line);
	home::Event event = home::makeEvent(line);

	m_queue.enqueue(event);

    return true;
}

void TcpServer::stop()
{
    m_stop = true;
	home::Event poisoned;
	poisoned.poisoned = true;
	m_queue.enqueue(poisoned);
}

void TcpServer::closeClientSockets()
{		
	for(auto it : m_clientSockets)
	{	
		close(it);
	}
}


}//namespace home