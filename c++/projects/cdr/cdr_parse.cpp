#include "cdr_parse.hpp"
#include "blocking_queue.hpp"
#include "ThreadPool/ThreadPool.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace cdr
{

CdrParse::CdrParse()
: m_cdrMap()
{
    initCdrMap();
}

void CdrParse::initCdrMap()
{
    m_cdrMap["MOC"] = Cdr::UsageType::MOC;//outgoing voice call
    m_cdrMap["MTC"] = Cdr::UsageType::MTC;//incoming voice call
    m_cdrMap["SMS-MO"] = Cdr::UsageType::SMS_MO;//outgoing message
    m_cdrMap["SMS-MT"] = Cdr::UsageType::SMS_MT;//incoming message
    m_cdrMap["D"] = Cdr::UsageType::D;//Data recived or transmitted
    m_cdrMap["U"] = Cdr::UsageType::U;//call not answered
    m_cdrMap["B"] = Cdr::UsageType::B;//busy call
    m_cdrMap["X"] = Cdr::UsageType::X;//failed call
}

std::vector<Cdr> CdrParse::fileParser(const std::string& a_path) const
{
    
    std::vector<Cdr> parsedCdrs;
    mt::BlockingQueue<Cdr> cdrsQueue(QUEUE_TASKS_SIZE);

    auto task = [this, &cdrsQueue](std::string const& a_line)
    {
        cdrsQueue.enqueue(this->lineParser(a_line));
    };
    
    std::string line;
    std::ifstream file(a_path);
    ThreadPool pool(NUM_OF_THREADS);
    std::getline(file, line);

    while(std::getline(file, line)) 
    {
        // cdrsQueue.enqueue(this->lineParser(line));
        pool.enqueue([task]{return task;});
    }
    std::cout << cdrsQueue.size() <<std::endl;
    while(!cdrsQueue.isEmpty()) 
    {
        Cdr pCdr = cdrsQueue.dequeue();
        parsedCdrs.push_back(pCdr);
    }

    return parsedCdrs;
}

Cdr CdrParse::lineParser(std::string const& a_line) const
{
    std::stringstream line(a_line);
    Cdr cdr;
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
    cdr.m_imsiSecondParty = (cdr.m_usageType != Cdr::UsageType::D) ? std::stoul(token) : 0;

    std::getline(line, cdr.m_msisdnSecondParty, delimiter);

    return cdr;
}

}//namespace cdr