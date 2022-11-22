#include "sensors_manager.hpp"

namespace home
{

namespace impel
{

void* threadFunction(void* a_arg)
{
    std::unique_ptr<SensorAgent>* sensor = static_cast<std::unique_ptr<SensorAgent>*>(a_arg);
    sensor->get()->run();
    return 0;
}


} //namespace impel

SensorsManager::SensorsManager(std::ifstream& a_configFile)
: m_stop(false)
{
    loadSensors(a_configFile);
    size_t size = m_sensors.size();
    m_threads.reserve(size) ;
    for(size_t i = 0; i < size; ++i)
    {
        m_threads[i] = new home::Thread(impel::threadFunction, &m_sensors[i]);
    }
}

SensorsManager::~SensorsManager()
{
    for(auto e: m_threads)
    {
        e->join();
        delete e;
    }
}

void SensorsManager::stop()
{
    for(auto& e: m_sensors)
    {
        e->stop();
    }
}

void SensorsManager::loadSensors(std::ifstream& a_file)
{
    SensorsLoader loader;
    loader.readFile(a_file, m_sensors);   
}


}//namespace home