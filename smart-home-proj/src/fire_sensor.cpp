#include "fire_sensor.hpp"

#define STANDARD_AMOUNT_OF_SECONDS 3

namespace home
{

FireSensor::FireSensor(const char* a_serverIP, int a_serverPort)
: m_stop(false)
, m_buffer(new char[1000])
, m_client(a_serverIP, a_serverPort)
{

}

FireSensor::FireSensor(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort)
: m_id(a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
, m_buffer(new char[1000])
, m_client(a_serverIP, a_serverPort)
{
    std::cout << "fire sensor was born!\n";
}

FireSensor::~FireSensor()
{
    delete[] m_buffer;
}

void FireSensor::run()
{
    while(!m_stop)
    { 
        Event tempEvent;

        tempEvent.m_timeStamp = timeNow(); 
        tempEvent.m_eventType = m_field;
        tempEvent.m_payload = std::to_string(rand() % 200);  //amount of smoke detected
        tempEvent.m_floor = m_floor;
        tempEvent.m_room = m_room;  

        std::string line = home::makeLine(tempEvent);
        home::PackLine(line, m_buffer);
        m_client.sendAndReceiveData(m_buffer, line.size()+1);
        
        sleep(STANDARD_AMOUNT_OF_SECONDS);
    }
}

void FireSensor::stop()
{
    m_stop = true;
}

   
}// home namespace

