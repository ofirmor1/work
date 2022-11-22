#include "alarm_controller.hpp"

namespace home
{

using namespace std;

AlarmController::AlarmController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config)
: ControllerAgent(a_id,  a_type, a_field, a_room, a_floor, a_config)
, m_alarm()
{
    std::cout << "alarm controller was born!\n" << std::endl;
} 

void AlarmController::reactToEvent(home::Event& a_event)
{
    std::string alarm = a_event.m_payload;

    if (alarm == "true")
    {
        if(!m_alarm.mode())
        {
            m_alarm.turnOn();
        }
        else
        {
            std::cout << "---------------------------\n";
            std::cout << "\033[1;31malarm is already on\033[0m\n";
        }
    }
    else if(alarm == "false")
    {       
        if(m_alarm.mode())
        {
            m_alarm.turnOff();
        }
        else
        {
            std::cout << "---------------------------\n";
            std::cout << "\033[1;31malarm is already off\033[0m\n";
        }
    }
 }


}// namespace home
