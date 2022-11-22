#ifndef SENSOR_AGENT_HPP
#define SENSOR_AGENT_HPP

#include <string>

#include "device.hpp"

namespace home
{

class SensorAgent : public Device
{
public:
    typedef std::string String;

    SensorAgent();
    SensorAgent(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config, const char* a_serverIP, int a_serverPort);
    virtual ~SensorAgent();

    virtual String id() const;
    virtual String type() const;
    virtual String field() const;
    virtual String floor() const;
    virtual String room() const;

    virtual void setId(String& a_id);
    virtual void setType(String& a_type);
    virtual void setField(String& a_field);
    virtual void setFloor(String& a_floor);
    virtual void setRoom(String& a_room);

    virtual void run();
    virtual void stop(){}   

private:
    String m_id;
    String m_type;
    String m_field; 
    String m_room;
    String m_floor;
};


}// namespace

#endif//SENSOR_AGENT_HPP

