#include "mu_test.h"
#include "cdr.hpp"
#include <fstream>
#include <cstddef>

BEGIN_TEST(test)
using namespace cdr;  
    std::ifstream file("text.txt", std::ifstream::in);
    bool status = file.is_open();
    std::string line;
    // ASSERT_EQUAL(line.length(),118);
    std::getline(file, line); // exclude header from result;
    while (file.good() )
    {
        for(std::string line; getline( file, line ); )
        {
            printf("123\n");
            // printf("loop ");
            Cdr cdr;
            CdrLine c;
            c = cdr.lineParser(line);
            std::cout << c.m_sequenc << " ";
            std::cout << c.m_imsi << " ";
            std::cout << c.m_imei << " ";     
            std::cout << c.m_usageType << " ";   
            std::cout << c.m_msisdn << " ";   
            std::cout << c.m_date << " ";   
            std::cout << c.m_time << " ";   
            std::cout << c.m_duration << " ";   
            std::cout << c.m_bytesRx << " ";   
            std::cout << c.m_bytesTx << " ";   
            std::cout << c.m_partyIMSI << " ";   
            std::cout << c.m_partyMSISDN << " ";   
            std::cout << '\n';
        }
    }

    ASSERT_EQUAL(status, true);
    file.close();

END_TEST


BEGIN_SUITE(cdr_tests)
    TEST(test)

END_SUITE
