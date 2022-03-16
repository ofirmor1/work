#include "cdr.hpp"
// #include "blocking_queue.hpp"
#include "thread_pool.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

#define MAX_LINE_LEN 256

namespace cdr
{

Cdr::Cdr()
: m_cdrMap()
{
    initCdrMap();
}

void Cdr::initCdrMap()
{
    m_cdrMap["MOC"] = UsageType::MOC;
    m_cdrMap["MTC"] = UsageType::MTC;
    m_cdrMap["SMS-MO"] = UsageType::SMS_MO;
    m_cdrMap["SMS-MT"] = UsageType::SMS_MT;
    m_cdrMap["D"] = UsageType::D;
    m_cdrMap["U"] = UsageType::U;
    m_cdrMap["B"] = UsageType::B;
    m_cdrMap["X"] = UsageType::X;
}

std::vector<CdrLine> Cdr::fileParser(std::string const& a_filePath) const
{
    std::ifstream file(a_filePath);
    std::string line;
    // mt::BlockingQueue<Cdr> cdrsQueue();
    std::vector<CdrLine> parsedCdrs;
    std::getline(file, line);

    auto task = [this, &parsedCdrs](const std::string& a_line)
    {
        parsedCdrs.push_back(this->lineParser(a_line));
    };

    mt::ThreadPool<decltype(task)> threadPool(decltype(task));

    return parsedCdrs;  
}

CdrLine Cdr::lineParser(std::string const& a_line) const
{
    std::stringstream line(a_line);
    CdrLine cdr;
    std::string token;
    char delimiter = '|';
    
    std::getline(line, token, delimiter);
    cdr.m_sequenc = std::stoul(token);

    std::getline(line, token, delimiter);
    cdr.m_imsi = std::stoul(token);

    std::getline(line, cdr.m_imei, delimiter);

    std::getline(line, token, delimiter);
    cdr.m_usageType = m_cdrMap.at(token);

    std::getline(line, cdr.m_msisdn, delimiter);

    std::getline(line, cdr.m_date, delimiter);

    std::getline(line, cdr.m_time, delimiter);

    std::getline(line, token, delimiter);
    cdr.m_duration = std::stoul(token);

    std::getline(line, token, delimiter);
    cdr.m_bytesRx = std::stoul(token);

    std::getline(line, token, delimiter);
    cdr.m_bytesTx = std::stoul(token);

    std::getline(line, token, delimiter);
    cdr.m_partyIMSI = (cdr.m_usageType != UsageType::D) ? std::stoul(token) : 0;

    std::getline(line, cdr.m_partyMSISDN, delimiter);

    return cdr;
}

}//namespace cdr

