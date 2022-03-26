#ifndef BILLING_HPP
#define BILLING_HPP

#include <unordered_map>
#include <cstddef>
#include <string>
#include "second_party.hpp"

namespace cdr 
{

struct BillingInfo
{
    BillingInfo()
    : m_totalOutgoingVoiceCallDuration(0)
    , m_totalIncomingVoiceCallDuration(0)
    , m_totalDataTransferred(0)
    , m_totalDataReceived(0)
    , m_totalSmsSent(0)
    , m_totalSmsReceived(0)
    , m_secondPartyMap() {}

    size_t m_totalOutgoingVoiceCallDuration;
    size_t m_totalIncomingVoiceCallDuration;
    size_t m_totalDataTransferred;
    size_t m_totalDataReceived;
    size_t m_totalSmsSent;
    size_t m_totalSmsReceived;
    std::unordered_map<std::string, SecondParty> m_secondPartyMap; // Key: MSISDN
};

}// namespace cdr


#endif /*BILLING_HPP*/