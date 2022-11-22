#ifndef TEMPERATURE_SENSOE_HPP
#define TEMPERATURE_SENSOE_HPP

#include <string>
#include <cstdio> 
#include <cstdlib> 
#include <unistd.h>
#include <sstream>

#include "event.hpp"
#include "utils.hpp"
#include "client.hpp"
#include "protocol.hpp"
#include "event_router.hpp"
#include "sensor_agent.hpp"

namespace home
{

typedef std::string String;

class TemperatureSensor : public SensorAgent
{
public:
    TemperatureSensor(const char* a_serverIP, int a_serverPort);
    TemperatureSensor(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort);
    ~TemperatureSensor();

    void run();
    void stop();  

private:
    void setConfiguration(String& a_config);
    std::string extract(std::string& a_configuration, std::string a_parameter);

private:
    String m_id;
    String m_type; 
    String m_field;
    String m_room;
    String m_floor;
    String m_tempUnits;
    double m_lowBound;
    double m_highBound;
    double m_period;
    bool m_stop;
    char* m_buffer;
    home::TcpClient m_client;
};


}// home namespace

#endif//TEMPERATURE_SENSOE_HPP
