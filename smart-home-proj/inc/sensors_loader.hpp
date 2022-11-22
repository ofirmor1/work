#ifndef SENSORS_LOADER_HPP
#define SENSORS_LOADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

#include "sensor_agent.hpp"
#include "light_sensor.hpp"
#include "fire_sensor.hpp"
#include "temperature_sensor.hpp"

namespace home 
{

class SensorsLoader
{
public:
    SensorsLoader();
    void readFile(std::ifstream& file, std::vector< std::unique_ptr<SensorAgent>>& a_agents);
};

}// namespace


#endif//SENSORS_LOADER_HPP