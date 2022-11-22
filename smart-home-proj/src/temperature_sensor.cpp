#include "temperature_sensor.hpp"

namespace home
{
    
TemperatureSensor::TemperatureSensor(const char* a_serverIP, int a_serverPort)
: m_stop(false)
, m_buffer(new char[1000])
, m_client(a_serverIP, a_serverPort)
{

}

TemperatureSensor::TemperatureSensor(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort)
: m_id(a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
, m_stop(false)
, m_buffer(new char[1000])
, m_client(a_serverIP, a_serverPort)
{
    setConfiguration(a_config);   
    std::cout <<"temperature sensor was born!\n";
}

TemperatureSensor::~TemperatureSensor()
{
    delete[] m_buffer;
}

void TemperatureSensor::run()
{
    while(!m_stop)
    {
        Event tempEvent;

        tempEvent.m_timeStamp = timeNow(); 
        tempEvent.m_eventType = m_field;
        tempEvent.m_payload = std::to_string(rand() % 50);
        tempEvent.m_floor = m_floor;
        tempEvent.m_room = m_room;

        std::string line = home::makeLine(tempEvent);
        home::PackLine(line, m_buffer);
        m_client.sendAndReceiveData(m_buffer, line.size()+1);
        
        sleep(m_period);
    }
}

void TemperatureSensor::stop()
{
    m_stop = true;
}
    
void TemperatureSensor::setConfiguration(String& a_config)
{
    m_tempUnits = extract(a_config, "units:");   
    m_lowBound = std::stod(extract(a_config, "lower:"));
    m_highBound = std::stod(extract(a_config, "upper:"));
    m_period = std::stod(extract(a_config, "period:"));
}

std::string TemperatureSensor::extract(std::string& a_configuration, std::string a_parameter)
{
    string word;
    stringstream iss(a_configuration);
 
    while(iss >> word)
    {
        if(word.compare(a_parameter) == 0)
        {
            iss >> word;
            word.pop_back();
            break;  
        }
    }
    return word;
}


}// home namespace

