#ifndef REQUESTS_HANDLE_HPP
#define REQUESTS_HANDLE_HPP

#include "json.hpp"
#include "tcp_client.hpp"
#include <string>

namespace cdr
{

using  = nlohmann::json;
using string = std::string;

struct ReqParams
{
    ReqParams(string a_ip, string a_port, string a_operation, string a_key)
    : m_ip(a_ip)
    , m_port(a_port)
    , m_operation(a_operation)
    , m_key(a_key){}
    
    string m_ip;
    string m_port;
    string m_operation;
    string m_key;
};

class ReqHandle
{
inline static const string PROTOCOL = "http://";
inline static const string URL_DEL = "/";

public:
    ReqHandle(const char* a_ip, int const& a_port);

    ~ReqHandle() = default;
    ReqHandle(ReqHandle const& a_other) = delete;
    ReqHandle& operator&(ReqHandle const& a_other) = delete;

    ReqParams createRequest(json const& a_json);
    ReqParams parseReq(std::vector<string> a_vec);

    void sendRequest(string const& a_request);
    json getResponse();

    string getOperation()const;
    
private:
    cdr::TCPClient m_socket;
    
};

}//namespace cdr

#endif /*#ifndef REQUESTS_HANDLE_HPP*/