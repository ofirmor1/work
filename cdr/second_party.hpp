#ifndef SECOND_PARTY_HPP
#define SECOND_PARTY_HPP

#include <cstddef>

namespace cdr 
{

struct SecondParty 
{
    size_t m_totalVoiceCallDuration;
    size_t m_totalSmsExchanged;
};

}// namespace cdr

#endif /*SECOND_PARTY_HPP*/