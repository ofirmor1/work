
#include "billing_aggregator.hpp"

namespace cdr
{
BillingAggr::BillingAggr(size_t a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_mapOfBills)
: m_imsi(a_imsi)
, m_cdr(a_cdr)
, m_mapOfBills(a_mapOfBills)
{
    newBill();
}

void BillingAggr::newBill()
{
    if(m_mapOfBills.find(m_imsi) == m_mapOfBills.end())
    {
        BillingInfo bill;
        updateBill(bill);
        this->m_mapOfBills[m_imsi] = bill;
    }
    else
    {
        updateBill(m_mapOfBills[m_imsi]);
    }       
}
  
void BillingAggr::updateBill(BillingInfo& a_bill) const
{
    
    switch (this->m_cdr.m_usageType)
    {
    case Cdr::MOC:
        a_bill.m_totalOutgoingVoiceCallDuration += this->m_cdr.m_duration;
        break;
    
    case Cdr::MTC:
        a_bill.m_totalIncomingVoiceCallDuration += this->m_cdr.m_duration;
        break;

    case Cdr::SMS_MO:
        ++a_bill.m_totalSmsSent;
        break;

    case Cdr::SMS_MT:
        ++a_bill.m_totalSmsReceived;
        break;

    case Cdr::D:
        a_bill.m_totalDataReceived += this->m_cdr.m_bytesRx;
        a_bill.m_totalDataTransferred += this->m_cdr.m_bytesTx;
        break;

    case Cdr::U:
        break;

    case Cdr::B:
        break;

    case Cdr::X:
        break;
    }

    if(this->m_cdr.m_usageType != Cdr::D) // no cdr data usage
    {
        if(a_bill.m_secondPartyMap.find(m_cdr.m_msisdnSecondParty) == a_bill.m_secondPartyMap.end())
        {
            SecondParty sp;
            sp.m_totalSmsExchanged = (this->m_cdr.m_usageType == Cdr::SMS_MO || this->m_cdr.m_usageType == Cdr::SMS_MT) ? 1:0;
            sp.m_totalVoiceCallDuration = this->m_cdr.m_duration;
            a_bill.m_secondPartyMap[m_cdr.m_msisdnSecondParty] = sp;
        }
        else
        {
            SecondParty& sp = a_bill.m_secondPartyMap[m_cdr.m_msisdnSecondParty];
            sp.m_totalSmsExchanged += (this->m_cdr.m_usageType == Cdr::SMS_MO || this->m_cdr.m_usageType == Cdr::SMS_MT) ? 1:0;
            sp.m_totalVoiceCallDuration = this->m_cdr.m_duration;
        }
    }
}

}//namespace cdr
