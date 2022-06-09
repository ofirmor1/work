#include "tcp_server.hpp"

namespace cdr
{

TCPServer::TCPServer(BillingInfo& a_db)
:m_db(a_db){}

json TCPServer::getMsg(ReqHandle &a_req)
{
    nlohmann::json response = a_req.getResponse();
    BillingInfo data;
    response["voice-out"] = data.m_totalOutgoingVoiceCallDuration;
    response["voice-in"] = data.m_totalIncomingVoiceCallDuration;
    response["data-out"] = data.m_totalDataTransferred;
    response["data-in"] = data.m_totalDataReceived;
    response["sms-out"] = data.m_totalSmsSent;
    response["sms-in"] = data.m_totalSmsReceived;
    return response;
} 

}//namespace cdr

