#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>

namespace home
{

class Log
{
public:
    Log(std::ofstream& a_logFile);
    void writeToFile(std::string a_line);

private:
    std::ofstream& m_logFile;
};


}// home namespace

#endif//LOG_HPP

