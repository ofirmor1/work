#include "log.hpp"

namespace home
{

Log::Log(std::ofstream& a_logFile)
:m_logFile(a_logFile)
{

}

void Log::writeToFile(std::string a_line)
{
    m_logFile.seekp(0,std::ios::end);
    m_logFile << a_line << "\n";
}


}// home namespace


