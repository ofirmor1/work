#ifndef sensors_manager_HPP
#define sensors_manager_HPP
 
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>

#include "event.hpp"
#include "thread.hpp"
#include "sensor_agent.hpp"
#include "sensors_loader.hpp"

namespace home
{

class SensorsManager
{
public:
    SensorsManager(std::ifstream& a_configFile);
    ~SensorsManager();

    void stop();

private:
    SensorsManager(SensorsManager const& a_source);
    SensorsManager& operator=(SensorsManager const& a_source);
    void loadSensors(std::ifstream& a_file);

private:
    std::vector< std::unique_ptr<SensorAgent> > m_sensors;
    std::vector<home::Thread*> m_threads;
    bool m_stop; 
};


} //namespace home

#endif //sensors_manager_HPP


