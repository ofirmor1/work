#include "server_manager.hpp"

namespace home 
{

ServerManager::ServerManager(const char* a_ip, int a_port, std::ofstream& a_logFile, std::ifstream& a_configFile, int q_size)
: m_queue(q_size)
, m_log(a_logFile)
, m_server(a_ip, a_port, m_queue, m_log)
, m_router(m_queue, a_configFile)
{

}

void ServerManager::stop()
{
    m_server.stop();
    m_router.stop();
}


}//namespace home 