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
    static const size_t THREADS_NUMBER = 4;
    Cdr m_cdr;
    std::unordered_map<std::string, Cdr::UsageType> m_cdrMap;
};

}//namespace cdr

#endif /*#ifndef CDR_PARSE_HPP*/