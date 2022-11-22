#ifndef EVENT_ROUTER_HPP
#define EVENT_ROUTER_HPP
 
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>

#include "event.hpp"
#include "thread.hpp"
#include "subscribers.hpp"
#include "event_router.hpp"
#include "blocking_queue.hpp"
#include "controller_agent.hpp"
#include "controllers_loader.hpp"

namespace home
{

typedef std::string EventType;
typedef std::string Location;

class EventRouter
{
public:
    EventRouter(home::BlockingQueue<home::Event>& a_queue, std::ifstream& a_configFile);
    ~EventRouter();

    void runRouter();
    void stop();

private:
    EventRouter(EventRouter const& a_source);
    EventRouter& operator=(EventRouter const& a_source);
    void loadControllers(std::ifstream& a_file);
    void registr();

private:
    std::vector< std::unique_ptr<ControllerAgent> > m_controllers;
    home::BlockingQueue<home::Event>& m_queue;
    Subscribers m_subscribers;
    home::Thread* m_thread;
    bool m_stop; 
};


} //namespace home

#endif //EVENT_ROUTER_HPP