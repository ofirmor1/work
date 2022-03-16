#ifndef CDR_HPP
#define CDR_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include <unordered_map>

typedef enum UsageType
{
    MOC = 1, //outgoing voice call
    MTC, //incoming voice call
    SMS_MO, //outgoing message
    SMS_MT, //incoming message
    D, //Data
    U, //call not answered
    B, //busy call
    X //failed call
}UsageType;

namespace cdr
{
struct CdrLine
{
    size_t m_sequenc;
    size_t m_imsi;
    std::string m_imei;
    UsageType m_usageType;
    std::string m_msisdn;
    std::string m_date;
    std::string m_time;
    size_t m_duration;
    size_t m_bytesRx;
    size_t m_bytesTx;
    size_t m_partyIMSI;
    std::string m_partyMSISDN;
};

class Cdr
{
public:
    Cdr();

    std::vector<CdrLine> fileParser(std::string const& a_filePath) const;
    CdrLine lineParser(std::string const& a_line) const; 

private:
    void initCdrMap();

private:
    static const size_t THREADS_NUMBER = 4;
    CdrLine m_cdr;
    std::unordered_map<std::string, UsageType> m_cdrMap;
};


}//namespace cdr


#endif /*#ifndef CDR_HPP*/