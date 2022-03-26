#include "mu_test.h"
#include "cdr_parse.hpp"
#include "cdr.hpp"
#include "billing_aggregator.hpp"
#include "billing_info.hpp"
#include "operator_aggregator.hpp"
#include "operator_info.hpp"
// #include "database.hpp"
#include <fstream>
#include <cstddef>
#include <string>

#include <unordered_map>

BEGIN_TEST(test_cdr_parser)
using namespace cdr;
std::vector<Cdr> cdrVec;
CdrParse cp;
cdrVec = cp.fileParser("cdrtest.txt");
ASSERT_EQUAL(cdrVec[12].m_bytesRx, 100);

END_TEST


BEGIN_TEST(test_billing_aggregateor)
using namespace cdr;
std::vector<Cdr> cdrVec;
CdrParse cp;
cdrVec = cp.fileParser("cdrtest.txt");
std::unordered_map<size_t, BillingInfo> map;

for (auto c : cdrVec)
{
    BillingAggr ba(c.m_imsi, c, map);
}

std::cout << "Billing information for each subscriber: \n" << std::endl; 
for(auto const& elem : map)
{
    std::cout << "Subscriber: "<< elem.first << std::endl;
    std::cout << "Outgoing voice calls duration in total: " << elem.second.m_totalOutgoingVoiceCallDuration<< "\n";
    std::cout << "Incoming voice calls duration in total: " << elem.second.m_totalIncomingVoiceCallDuration << "\n";
    std::cout << "Total Data transferred in KB: " << elem.second.m_totalDataTransferred << "\n";
    std::cout << "Total Data received in KB: " << elem.second.m_totalDataReceived << "\n";
    std::cout << "Total SMS sent: " << elem.second.m_totalSmsSent << "\n";
    std::cout << "Total SMS received: " << elem.second.m_totalSmsReceived << "\n";
    std::cout << std::endl;
}

ASSERT_PASS();

END_TEST


BEGIN_TEST(test_operator_aggregateor)
using namespace cdr;
std::vector<Cdr> cdrVec;
CdrParse cp;
cdrVec = cp.fileParser("cdrtest.txt");
std::unordered_map<std::string, OperatorInfo> map;

for (auto c : cdrVec)
{
    std::string mccmnc = std::to_string(c.m_imsi).substr(3,2);
    OprAggr oa(mccmnc, c, map);
}

std::cout << "\n\nOperator information for each customer: \n" << std::endl; 
for(auto const& elem : map)
{
    std::cout << "operator: " << elem.first << std::endl;
    std::cout << "Outgoing voice calls duration in total: " << elem.second.m_totalOutgoingVoiceCallDuration<< "\n";
    std::cout << "Incoming voice calls duration in total: " << elem.second.m_totalIncomingVoiceCallDuration << "\n";
    std::cout << "Total SMS sent: " << elem.second.m_totalOutgoingSms << "\n";
    std::cout << "Total SMS received: " << elem.second.m_totalIncomingSms << "\n";
    std::cout << std::endl;
}

ASSERT_PASS();

END_TEST


BEGIN_SUITE(cdr_tests)
    TEST(test_cdr_parser)
    TEST(test_billing_aggregateor)
    TEST(test_operator_aggregateor)

END_SUITE
