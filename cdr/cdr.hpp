#ifndef CDR_HPP
#define CDR_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace cdr
{

struct Cdr
{
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
    size_t m_imsiSecondParty;
    std::string m_msisdnSecondParty;
};

}//namespace cdr

#endif /*#ifndef CDR_HPP*/