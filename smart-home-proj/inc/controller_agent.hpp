#ifndef CONTROLLER_AGENT_HPP
#define CONTROLLER_AGENT_HPP

#include <set>
#include <string>

#include "event.hpp"
#include "device.hpp"

using namespace std;

namespace home
{

class ControllerAgent : public Device
{
public:
    ControllerAgent();
    ControllerAgent(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config);
    virtual ~ControllerAgent();
    
    string id() const;
    string type() const;
    string field() const;
    string floor() const;
    string room() const;
    string config() const;
    
    void AcceptEvent(home::Event& a_event);
    virtual void reactToEvent(home::Event& a_event);    
    
    virtual void setId(String& a_id);
    virtual void setType(String& a_type);
    virtual void setField(String& a_field);
    virtual void setFloor(String& a_floor);
    virtual void setRoom(String& a_room);
    virtual void run();
    
private:
    string m_id;
    string m_type;
    string m_field;
    string m_room;
    string m_floor;
    string m_config;
};


}// namespace

#endif//CONTROLLER_AGENT_HPP