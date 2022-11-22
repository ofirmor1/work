#include "temperature_controller.hpp"

using namespace std;

namespace home
{

TemperatureController::TemperatureController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config)
: ControllerAgent(a_id,  a_type, a_field, a_room, a_floor, a_config)
, m_airConditioner()
{
    std::cout <<"temperature controller was born!\n" << std::endl;
} 

void TemperatureController::reactToEvent(home::Event& a_event)
{
    int temprature = stoi(a_event.m_payload);
    std::cout << "---------------------------\n";
    std::cout << "\033[1;32mthe temprature is :" << temprature << "\033[0m\n";

    if(temprature < 20)
    {
        if(!m_airConditioner.isOn())
        {
            m_airConditioner.turnOnHeat();
        }
        else if(!m_airConditioner.mode())
        {
            m_airConditioner.changeMode();
        }
        else
        {
            std::cout << "\033[1;32mair conditioner is already on heat\033[0m\n";
        }
    }

    if(temprature > 20 && temprature < 25)
    {
        if(m_airConditioner.isOn())
        {
            m_airConditioner.turnOff();
        }
        std::cout << "\033[1;32mNo need for air conditioning\033[0m\n";
    }

    if(temprature > 25)
    {
        if(!m_airConditioner.isOn())
        {
            m_airConditioner.turnOnCold();
        }
        else if(m_airConditioner.mode())
        {
            m_airConditioner.changeMode();
        }
        else
        {
            std::cout << "\033[1;32mair conditioner is already on cold\033[0m\n";
        }
    }

}


}//namespace home
