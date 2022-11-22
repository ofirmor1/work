#include "light_controller.hpp"

using namespace std;

namespace home
{

LightController::LightController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config)
: ControllerAgent(a_id,  a_type, a_field, a_room, a_floor, a_config)
, m_bulb()
{
    std::cout <<"light controller was born!\n" << std::endl;
} 

void LightController::reactToEvent(home::Event& a_event)
{
    std::string light = a_event.m_payload;
    if(light == "false")
    {
        std::cout << "---------------------------\n";
        std::cout << "\033[1;33mThere is daylight outside\033[0m\n";
    }
    if(light == "true")
    {
        std::cout << "---------------------------\n";
        std::cout << "\033[1;33mIt is dark outside\033[0m\n";
    }

    if (light == "true")
    {
        if(!m_bulb.mode())
        {
            m_bulb.turnOn();
        }
        else
        {
            std::cout << "\033[1;33mThe light is already on\033[0m\n";
        }
    }
    else if(light == "false")
    {
        if(m_bulb.mode())
        {
            m_bulb.turnOff();
        }
        else
        {
            std::cout << "\033[1;33mThe light is already off\033[0m\n";
        }
    }
}


}//namespace
