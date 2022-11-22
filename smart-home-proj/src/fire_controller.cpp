#include "fire_controller.hpp"

using namespace std;

namespace home
{

FireController::FireController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config, const char* a_serverIP, int a_serverPort)
: ControllerAgent(a_id,  a_type, a_field, a_room, a_floor, a_config)
, m_id(a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
, m_sprinkler()
, m_client(a_serverIP, a_serverPort)
, m_buffer(new char[1000])
{
    std::cout <<"fire controller was born!\n" << std::endl;
} 

FireController::~FireController()
{
    delete[] m_buffer;
}

void FireController::reactToEvent(home::Event& a_event)
{
    std::string fire = a_event.m_payload;
    std::cout << "---------------------------\n";
    std::cout << "\033[1;31mConcentration of smoke: " << fire << "\033[0m\n";
     
    if (stoi(fire) > 100)
    {
        if(!m_sprinkler.mode())
        {
            m_sprinkler.turnOn();
        }
        else
        {
            std::cout << "\033[1;31msprinkler is already on\033[0m\n";
        }
        sendFireEvent();    
    }
    if (stoi(fire) < 100)
    {
        if(m_sprinkler.mode())
        {  
            m_sprinkler.turnOff();
        }
        else
        {
            std::cout << "\033[1;31msprinkler is already off\033[0m\n";
        }
        sendFireWentOut();
    }
}

void FireController::sendFireEvent()
{
    Event tempEvent;

    tempEvent.m_timeStamp = timeNow(); 
    tempEvent.m_eventType = "alarm";
    tempEvent.m_payload = "true";
    tempEvent.m_floor = m_floor;
    tempEvent.m_room = m_room;  
    
    std::string line = home::makeLine(tempEvent);
    home::PackLine(line, m_buffer);
    m_client.sendAndReceiveData(m_buffer, line.size()+1);      
}

void FireController::sendFireWentOut()
{
    Event tempEvent;

    tempEvent.m_timeStamp = timeNow(); 
    tempEvent.m_eventType = "alarm";
    tempEvent.m_payload = "false";
    tempEvent.m_floor = m_floor;
    tempEvent.m_room = m_room; 
    
    std::string line = home::makeLine(tempEvent);
    home::PackLine(line, m_buffer);
    m_client.sendAndReceiveData(m_buffer, line.size()+1);     
}


}//namespace home
