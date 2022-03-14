#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <cstddef>

namespace cdr
{

class Operator
{
public:
    Operator();

private:
    size_t m_mnc;
    size_t m_voiceOut;// outcoming CALL in sec;
    size_t m_voiceIn;// incoming CALL in sec;
    size_t m_SmsOut;// outcoming SMS
    size_t m_SmsIn;// incoming SMS
};

}//namespace cdr

#endif /*#ifndef OPERATOR_HPP*/