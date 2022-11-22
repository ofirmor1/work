#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include "event.hpp"

namespace home
{
    
class Device
{
public:
    typedef std::string String;

    Device();
    Device(String const& a_id, String const& a_type, String const& a_field, String const& a_room, String const& a_floor, String a_config);
    Device(Device const& a_source) = delete;
    virtual Device& operator=(Device const& a_source) = delete;
    virtual ~Device();

    virtual String id() const = 0;
    virtual String type() const = 0;
    virtual String field() const = 0;
    virtual String floor() const = 0;
    virtual String room() const = 0;

    virtual void setId(String& a_id) = 0;
    virtual void setType(String& a_type) = 0;
    virtual void setField(String& a_field) = 0;
    virtual void setFloor(String& a_floor) = 0;
    virtual void setRoom(String& a_room) = 0;

private:
    String m_id;
    String m_type; 
    String m_floor;
    String m_room;
};


}// namespace home

#endif//DEVICE_HPP

