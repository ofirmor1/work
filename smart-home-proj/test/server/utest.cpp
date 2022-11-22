#include "mu_test.h"
#include <iostream>
#include <unistd.h>
#include <conio.h> // getch() kbhit()
#include "log.hpp"
#include "server_manager.hpp"

BEGIN_TEST(server_and_controlers)

    std::ofstream logPath("../../log/log.txt", std::ios::app);
    std::ifstream configFile("../../configFile/controler_config.txt");
    home::ServerManager server("0.0.0.0", 5555, logPath, configFile);

    while(1)
    {
        if( kbhit() )
        {
            if( 'q' == getch() )
            {
                server.stop();
                break;
            }
        }
    }

    ASSERT_PASS();

END_TEST


BEGIN_SUITE(server_and_controlers)

    TEST(server_and_controlers)

END_SUITE
