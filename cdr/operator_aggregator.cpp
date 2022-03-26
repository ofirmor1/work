#include "operator_aggregator.hpp"

#include <cstddef>

namespace cdr
{
OprAggr::OprAggr(std::string const& a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_mapOfOperators)
: m_mccmnc(a_mccmnc)
, m_cdr(a_cdr)
, m_mapOfOperators(a_mapOfOperators)
{
    newOperator();
}

void OprAggr::newOperator()
{
    if(m_mapOfOperators.find(m_mccmnc) == m_mapOfOperators.end())
    {
        OperatorInfo Operator;
        updateOperator(Operator);
        this->m_mapOfOperators[m_mccmnc] = Operator;
    }
    else
    {
        updateOperator(m_mapOfOperators[m_mccmnc]);
    }       
}

void OprAggr::updateOperator(OperatorInfo& a_operator) const
{
    switch (this->m_cdr.m_usageType)
    {
    case Cdr::MOC:
        a_operator.m_totalOutgoingVoiceCallDuration += this->m_cdr.m_duration;
        break;
    
    case Cdr::MTC:
        a_operator.m_totalIncomingVoiceCallDuration += this->m_cdr.m_duration;
        break;

    case Cdr::SMS_MO:
        ++a_operator.m_totalOutgoingSms;
        break;

    case Cdr::SMS_MT:
        ++a_operator.m_totalIncomingSms;
        break;

    case Cdr::D:
        break;

    case Cdr::U:
        break;

    case Cdr::B:
        break;

    case Cdr::X:
        break;
    }
}

}//namespace cdr