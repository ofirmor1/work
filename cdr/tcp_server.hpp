#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "json.hpp"
#include "requests_handle.hpp"
#include "billing_info.hpp"
#include <iostream>

namespace cdr
{
using json = nlohmann::json;

class TCPServer
{
public:
    TCPServer(BillingInfo& a_db);
    ~TCPServer() = default;

    json getMsg(ReqHandle &a_req);

private:
    BillingInfo& m_db;
};

}//namespace cdr

#endif /*#ifndef TCP_SERVER_HPP*/