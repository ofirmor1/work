#include "event_router.hpp"

namespace home
{

namespace impel
{

void* threadFunction(void* a_arg)
{
    EventRouter* er = static_cast<EventRouter*>(a_arg);
    er->runRouter();
    return 0;
}


} //namespace impel

EventRouter::EventRouter(home::BlockingQueue<home::Event>& a_queue, std::ifstream& a_configFile)
: m_queue(a_queue)
, m_subscribers()
, m_stop(false)
{
    loadControllers(a_configFile); 
    registr();
    m_thread = new home::Thread(impel::threadFunction, this);
}

EventRouter::~EventRouter()
{
    m_thread->join();
    delete m_thread;
}

void EventRouter::runRouter()
{
    while (!m_stop)
    {
        home::Event event;
        m_queue.dequeue(event);

        if(!event.poisoned)
        {
            std::vector<ControllerAgent*> enrolled;
            m_subscribers.get(event, enrolled);

            for(auto& controller : enrolled)
            {
                controller->reactToEvent(event);
            }
        }
    }
}

void EventRouter::stop()
{
    m_stop = true;
}

void EventRouter::loadControllers(std::ifstream& a_file)
{
    ControllersLoader loader;
    loader.readFile(a_file, m_controllers); 
}

void EventRouter::registr()
{
    m_subscribers.initialize(m_controllers);
}   


}//namespace home