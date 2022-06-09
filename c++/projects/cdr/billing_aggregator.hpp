#ifndef BILLING_TASK_HPP
#define BILLING_TASK_HPP

#include "cdr.hpp"
#include "billing_info.hpp"
#include<unordered_map>

namespace cdr
{
class BillingAggr
{

public:
    BillingAggr(size_t a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_mapOfBills);

    void newBill();

    void updateBill(BillingInfo& a_bill) const;

private:
    size_t m_imsi;
    Cdr m_cdr;
    std::unordered_map<size_t, BillingInfo>& m_mapOfBills;
};

}//namespace cdr

#endif /*#ifndef BILLING_TASK_HPP*/