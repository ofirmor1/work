#include "sensor_agent.hpp"

namespace home
{

typedef std::string String;

SensorAgent::SensorAgent()
{

}

SensorAgent::SensorAgent(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort)
: m_id(a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
{

}

SensorAgent::~SensorAgent()
{

}

String SensorAgent::id() const
{
    return m_id;
}

String SensorAgent::type() const
{
    return m_type;
}

String SensorAgent::field() const
{
    return m_field;
}

String SensorAgent::floor() const
{
    return m_floor;
}

String SensorAgent::room() const
{
    return m_room;
}

void SensorAgent::setId(String& a_id)
{
    m_id = a_id;
}

void SensorAgent::setType(String& a_type)
{
    m_type = a_type;
}

void SensorAgent::setField(String& a_field)
{
    m_field = a_field;
}

void SensorAgent::setFloor(String& a_floor)
{
    m_floor = a_floor;
}

void SensorAgent::setRoom(String& a_room)
{
    m_room = a_room;
}

void SensorAgent::run()
{
   
}


}//namespace
