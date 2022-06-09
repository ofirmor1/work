#ifndef OPERATOR_INFO_HPP
#define OPERATOR_INFO_HPP

#include <cstddef>

namespace cdr
{

struct OperatorInfo
{
    OperatorInfo()
    : m_totalIncomingVoiceCallDuration(0)
    , m_totalOutgoingVoiceCallDuration(0)
    , m_totalIncomingSms(0)
    , m_totalOutgoingSms(0) {}

    size_t m_totalIncomingVoiceCallDuration;// in sec
    size_t m_totalOutgoingVoiceCallDuration;// in sec
    size_t m_totalIncomingSms;
    size_t m_totalOutgoingSms;
};

}//namespace cdr

#endif /*#ifndef OPERATOR_INFO_HPP*/