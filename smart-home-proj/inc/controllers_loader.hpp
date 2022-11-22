#ifndef CONTOLLERS_LOADER_HPP
#define CONTOLLERS_LOADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>

#include "controller_agent.hpp"
#include "light_controller.hpp"
#include "fire_controller.hpp"
#include "alarm_controller.hpp"
#include "temperature_controller.hpp"

namespace home 
{

class ControllersLoader
{
public:
    ControllersLoader();
    void readFile(std::ifstream& file, std::vector< std::unique_ptr<ControllerAgent>>& a_agents);
};


}// namespace home

#endif//CONTOLLERS_LOADER_HPP