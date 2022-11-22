#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

namespace home
{
    
typedef std::string String;

class Event
{
public:
    Event()
    :m_timeStamp()
    ,m_eventType()
    ,m_payload()
    ,m_floor()
    ,m_room()
    ,poisoned(false){};

    String m_timeStamp;
    String m_eventType;
    String m_payload;
    String m_floor;
    String m_room;
    bool poisoned;
};


}// home namespace

#endif//EVENT_HPP

