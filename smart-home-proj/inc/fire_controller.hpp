#ifndef FIRE_CONTROLLER_HPP
#define FIRE_CONTROLLER_HPP

#include <iostream>
#include <string>

#include "utils.hpp"
#include "event.hpp"
#include "client.hpp"
#include "protocol.hpp"
#include "sprinkler.hpp"
#include "controller_agent.hpp"

using namespace std;

namespace home
{

class FireController : public ControllerAgent
{

public:
    FireController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config, const char* a_serverIP = "", int a_serverPort = 0);  
    ~FireController();

    void reactToEvent(home::Event& a_event);
    void sendFireEvent();
    void sendFireWentOut();

private:
    String m_id;
    String m_type; 
    String m_field;
    String m_room;
    String m_floor;
    Sprinkler m_sprinkler;
    home::TcpClient m_client;
    char* m_buffer;
};


}// namespace

#endif//FIRE_CONTROLLER_HPP