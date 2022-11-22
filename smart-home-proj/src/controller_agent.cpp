#include "controller_agent.hpp"

namespace home
{

ControllerAgent::ControllerAgent()
{
    
}

ControllerAgent::ControllerAgent(string const& a_id, string const& a_type, String const& a_field, string const& a_room, string const& a_floor, string a_config)
: m_id (a_id)
, m_type(a_type)
, m_field(a_field)
, m_room(a_room)
, m_floor(a_floor)
, m_config(a_config)
{

}

ControllerAgent::~ControllerAgent()
{

}

string ControllerAgent::id() const
{
    return m_id;
}

string ControllerAgent::type() const
{
    return m_type;
}

string ControllerAgent::field() const
{
    return m_field;
}

string ControllerAgent::floor() const
{
    return m_floor;
}

string ControllerAgent::room() const
{
    return m_room;
}

string ControllerAgent::config() const
{
    return m_config;
}

void ControllerAgent::setId(String& a_id)
{
    m_id = a_id;
}

void ControllerAgent::setType(String& a_type)
{
    m_type = a_type;
}

void ControllerAgent::setField(String& a_field)
{
    m_field = a_field;
}

void ControllerAgent::setFloor(String& a_floor)
{
    m_floor = a_floor;
}

void ControllerAgent::setRoom(String& a_room)
{
    m_room = a_room;
}

void ControllerAgent::run()
{  

}

void ControllerAgent::AcceptEvent(home::Event& a_event)
{

}

void ControllerAgent::reactToEvent(home::Event& a_event)
{
    
}


}//namespace