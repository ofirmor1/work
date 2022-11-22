#ifndef TEMPAGENT_HPP
#define TEMPAGENT_HPP

#include "event.hpp"
#include "air_conditioner.hpp"
#include "controller_agent.hpp"

using namespace std;

namespace home
{

class TemperatureController : public ControllerAgent
{
public:
    TemperatureController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config);  
    void reactToEvent(home::Event& a_event);

private:
    AirConditioner m_airConditioner;
};


}// namespace

#endif//TEMPAGENT_HPP