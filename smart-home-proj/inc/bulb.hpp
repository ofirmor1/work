#ifndef BULB_HPP
#define BULB_HPP

#include <iostream>

namespace home
{

class Bulb
{
public:
    Bulb()
    :m_status(false)
    {}

    bool isOn() const
    {
        return m_status;
    }

    bool mode() const
    {
        return m_mode;
    }

    void turnOn()
    {
        m_status = true; 
        m_mode = true; 
        std::cout << "\033[1;33mBulb is turn on\033[0m\n";
    }

     void turnOff()
    {
        m_status = false;
        m_mode = false; 
        std::cout << "\033[1;33mBulb turn off\033[0m\n";
    }
   
private:
    bool m_status;
    bool m_mode;
};


}// namespace home

#endif //BULB_HPP