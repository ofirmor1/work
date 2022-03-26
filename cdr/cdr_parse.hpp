#ifndef CDR_PARSE_HPP
#define CDR_PARSE_HPP

#include "cdr.hpp"
#include <vector>
#include <string>
#include <unordered_map>

namespace cdr
{

class CdrParse
{
public:
    CdrParse();

    std::vector<Cdr> fileParser(const std::string& a_path) const;
    Cdr lineParser(std::string const& a_line) const; 

private:
    void initCdrMap();

private:
    Cdr m_cdr;
    std::unordered_map<std::string, Cdr::UsageType> m_cdrMap;
    static const int QUEUE_TASKS_SIZE = 50;
    static const int NUM_OF_THREADS = 4;
};

}//namespace cdr

#endif /*#ifndef CDR_PARSE_HPP*/