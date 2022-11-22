#ifndef ALARM_CONTROLER_HPP
#define ALARM_CONTROLER_HPP

#include "controller_agent.hpp"
#include "event.hpp"
#include "alarm.hpp"

using namespace std;

namespace home
{

class AlarmController : public ControllerAgent
{
public:
    AlarmController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config);  

    void reactToEvent(home::Event& a_event);

private:
    Alarm   m_alarm;
};


}// namespace home

#endif //ALARM_CONTROLER_HPP