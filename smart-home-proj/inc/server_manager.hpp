#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <fstream>

#include "blocking_queue.hpp"
#include "event_router.hpp"
#include "server.hpp"
#include "event.hpp"

namespace home
{

class ServerManager
{
public:
    ServerManager(const char* a_ip, int a_port, std::ofstream& a_logFile, std::ifstream& a_configFile, int q_size = 1000);
    void stop();

private:
    home::BlockingQueue<home::Event> m_queue;
    home::Log m_log;
    home::TcpServer m_server;
    home::EventRouter m_router;
};


} //namespace cdr

#endif//SERVER_MANAGER_HPP