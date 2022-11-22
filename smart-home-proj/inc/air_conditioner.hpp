#ifndef AIR_CONDITION_HPP
#define AIR_CONDITION_HPP

#include <iostream>

namespace home
{

class AirConditioner 
{
public:
    AirConditioner()
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

    void turnOnHeat()
    {
        m_status = true; 
        m_mode = true; 
        std::cout << "\033[1;32mAir conditioner turn on on heat\033[0m\n";
    }

    void turnOnCold()
    {
        m_status = true; 
        m_mode = false; 
        std::cout << "\033[1;32mAir conditioner turn on on cold\033[0m\n";
    }

    void turnOff()
    {
        m_status = false; 
        std::cout << "\033[1;32mAir conditioner turn off\033[0m\n";
    }

    void changeMode()
    {
        if(m_mode == 0)
        {
            m_mode = 1;  
            std::cout << "\033[1;32mAir conditioner mode change to heat\033[0m\n";
        }
        else
        {
            m_mode = 0; 
            std::cout << "\033[1;32mAir conditioner mode change to cold\033[0m\n";
        }
    }

private:
    bool m_status;
    bool m_mode;
};


}// namespace

#endif //AIR_CONDITION