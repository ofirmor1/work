#include "tasks.hpp"
#include "billing_aggregator.hpp"
#include "operator_aggregator.hpp"

namespace cdr
{
void* Tasks::addBillingTask(const size_t a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_map)
{
    return new BillingAggr(a_imsi, a_cdr, a_map);
}

void* updateBillingTask(const size_t  a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_map)
{
    return new BillingAggr(a_imsi, a_cdr, a_map);
}

void* Tasks::addOperatorTask(std::string const& a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_map)
{
    return new OprAggr(a_mccmnc, a_cdr, a_map);
}

void* Tasks::updateOperatorTask(std::string const& a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_map)
{
    return new OprAggr(a_mccmnc, a_cdr, a_map);
}

// void* Tasks::linkGraphTask(const size_t a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_map)
// {
//     return new OprAggr(a_mccmnc, a_cdr, a_map);
// }




}//namespace cdr