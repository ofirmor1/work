#include "mu_test.h"
#include <fstream>
#include <conio.h> // getch() kbhit()
#include "sensors_manager.hpp"

BEGIN_TEST(sensor_manager)

    std::ifstream configFile("../../configFile/sensor_config.txt");
    home::SensorsManager sensorManager(configFile);
 
    while(1)
    {

        if( kbhit() )
        {
            if( 'q' == getch() )
            {
                sensorManager.stop();
                break;
            }
        }
    }

    ASSERT_PASS();
    
END_TEST


BEGIN_SUITE(sensor_manager)

    TEST(sensor_manager)

END_SUITE
