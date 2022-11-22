#include "light_sensor.hpp"

#define STANDARD_AMOUNT_OF_SECONDS 3

namespace home
{

LightSensor::LightSensor(const char* a_serverIP, int a_serverPort)
: m_stop(false)
, m_client(a_serverIP, a_serverPort)
{

}

LightSensor::LightSensor(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort)
: m_id(a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
, m_buffer(new char[1000])
, m_client(a_serverIP, a_serverPort)
{
    std::cout << "light sensor was born!\n";
}

LightSensor::~LightSensor()
{
    delete[] m_buffer;
}

void LightSensor::run()
{
    size_t counter = 0;
    while(!m_stop)
    { 
        Event tempEvent;

        if(counter%2 == 0)
        {
            m_isItDark  = true;
            tempEvent.m_payload = "true";
        }
        else
        {
           m_isItDark  = false; 
           tempEvent.m_payload = "false";
        } 

        tempEvent.m_timeStamp = timeNow(); 
        tempEvent.m_eventType = m_field;
        tempEvent.m_floor = m_floor;
        tempEvent.m_room = m_room;
          
        std::string line = home::makeLine(tempEvent);
        home::PackLine(line, m_buffer);
        m_client.sendAndReceiveData(m_buffer, line.size()+1);
        
        sleep(STANDARD_AMOUNT_OF_SECONDS); 
        ++counter;
    }
}

void LightSensor::stop()
{
    m_stop = true;
}

    
}// home namespace

