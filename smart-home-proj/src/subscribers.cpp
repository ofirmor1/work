#include "subscribers.hpp"

namespace home
{

Subscribers::Subscribers()
{

}

Subscribers::Subscribers(std::vector<std::unique_ptr<ControllerAgent> >& a_controllers)
{

}

void Subscribers::initialize(std::vector<std::unique_ptr<ControllerAgent> >& a_controllers)
{
    for(auto& cont: a_controllers)
    {
        add(cont);
    }
}

void Subscribers::add(unique_ptr<ControllerAgent>& a_controller)
{
    std::string key; 
    key = createKey(a_controller->field(), a_controller->room());
    m_subscribers[key].insert({a_controller->id(), std::move(a_controller)});
}

void Subscribers::unsubscribe(unique_ptr<ControllerAgent>& a_controller)
{
    std::string key;
    key = createKey(a_controller->field(), a_controller->room());    
    m_subscribers[key].erase(a_controller->id());
}

void Subscribers::get(Event const& a_event, vector<ControllerAgent*>& a_controllers)
{
    std::string key;
    key = createKey(a_event.m_eventType, a_event.m_room);
    for(auto& it: m_subscribers[key]) 
    {
        ControllerAgent* cont = it.second.get();
        a_controllers.push_back(cont); 
    }
}

std::string Subscribers::createKey(std::string const& a_field, std::string const& a_room)
{
    std::string key(a_field + "|" + a_room);
    return key;
}


} //namespace home