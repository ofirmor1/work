#ifndef SUBSCRIBERS_HPP
#define SUBSCRIBERS_HPP

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>

#include "event.hpp"
#include "controller_agent.hpp"

namespace home
{

typedef std::string EventKey;
typedef std::string IdKey;
using namespace std;

class Subscribers
{
public:
    Subscribers();
    Subscribers(vector<unique_ptr<ControllerAgent> >& a_controllers);

    void initialize(std::vector<std::unique_ptr<ControllerAgent> >& a_controllers);
    void add(unique_ptr<ControllerAgent>& a_controller);
    void unsubscribe(unique_ptr<ControllerAgent>& a_controller);
    void get(Event const& a_event, vector<ControllerAgent*>& a_controllers);

private:
    std::string createKey(std::string const& a_field, std::string const& a_room);

private:
    unordered_map<EventKey, unordered_map<IdKey, unique_ptr<ControllerAgent>>> m_subscribers;
};


} //namespace home

#endif //SUBSCRIBERS_HPP