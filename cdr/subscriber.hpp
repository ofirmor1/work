#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <cstddef>

namespace cdr
{

class Subscriber
{
public:
    Subscriber();

private:
    size_t m_msisdn;
    size_t m_mocExt; // outcoming CALL for external operator;
    size_t m_mocInt; // outcoming CALL for internal operator;
    size_t m_motExt; // incoming CALL from external operator;
    size_t m_motInt; // incoming CALL from internal operator;
    size_t m_incSmsExtOpr; // incoming SMS from external operator;
    size_t m_outSmsExtOpr; // outcoming SMS for external operator;
    size_t m_incSmsIntOpr; // incoming SMS FROM internal operator;
    size_t m_outSmsIntOpr; // outcoming SMS for internal operator;
    size_t m_upload;
    size_t m_download;
};

}//namespace cdr

#endif /*#ifndef SUBSCRIBER_HPP*/