#ifndef LIGHTAGENT_HPP
#define LIGHTAGENT_HPP

#include "controller_agent.hpp"
#include "event.hpp"
#include "bulb.hpp"

using namespace std;

namespace home
{

class LightController : public ControllerAgent
{
public:
    LightController(string const& a_id, string const& a_type, string const& a_field, string const& a_room, string const& a_floor, string a_config);  
    void reactToEvent(home::Event& a_event);

private:
    Bulb m_bulb;
};


}// namespace

#endif//LIGHTAGENT_HPP