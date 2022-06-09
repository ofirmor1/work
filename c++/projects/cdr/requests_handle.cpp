#include "requests_handle.hpp"
#include "json.hpp"
#include <string>
#include <sstream>

#define BUFFER_SIZE 4096

namespace cdr
{
using json = nlohmann::json;

static int strToInt(string a_str);
static string getIP(string a_str);
static string getPort(string a_str);


ReqHandle::ReqHandle(const char* a_ip, int const& a_port)
: m_socket(a_ip, a_port)
{
    this->m_socket.connectServer();
}

void ReqHandle::sendRequest(string const& a_request)
{

    this->m_socket.sendData(a_request.c_str(), (a_request.length() + 1));
}

json ReqHandle::getResponse()
{
    char* buffer = this->m_socket.receiveData(BUFFER_SIZE);
    return json::parse(reinterpret_cast<const char*>(buffer));
}   

ReqParams ReqHandle::createRequest(json const& a_json)
{
    string req = a_json["URL Request"];
    req.erase(0, PROTOCOL.length());
    int counter = 0 , lastIndex = 0;
    std::vector<string> requestVector;
    for(int i = 0 ; req[i] != '\0' ; ++i)
    {
        if(req[i] == '/')
        {
            string res = req.substr(lastIndex , counter);
            counter = 0;
            lastIndex = i + 1;
            requestVector.push_back(res);
            continue;
        }
        if(req[i+1] == '\0')
        {
            string res = req.substr(lastIndex , counter + 1);
            requestVector.push_back(res);
            continue;
        }
        ++counter;
    }
    ReqParams newReq = parseReq(requestVector);
    return newReq;
}

ReqParams ReqHandle::parseReq(std::vector<string> a_vec)
{
    string domain = a_vec[0];
    string operation = a_vec[2];
    string key = a_vec[3];

    string ip = getIP(domain);
    string port = getPort(domain);

    return ReqParams(ip, port, operation, key);
}

static int strToInt(string a_str) {
    int res = 0;
    std::stringstream str(a_str);
    str >> res;
    return res;
}

static string getIP(string a_str)
{
    int start = 0;
    int end = a_str.find(":");
    return a_str.substr(start, end - start);
}

static string getPort(string a_str)
{
    int start = a_str.find(":") + 1;
    int end = a_str.size();
    return a_str.substr(start, end - start);
}

}//namespace cdr