#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include<vector>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include"event.hpp"

namespace home
{
    
std::string makeLine(home::Event a_event);
int PackLine(std::string a_line, void* a_buffer);
std::string UnpackLine(void* a_buffer);
home::Event makeEvent(std::string a_line);


} //namespace home

#endif  //PROTOCOL_HPP