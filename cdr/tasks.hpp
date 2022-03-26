#ifndef PRODUCE_REPORT_HPP
#define PRODUCE_REPORT_HPP

#include<unordered_map>
#include "cdr.hpp"
#include "billing_info.hpp"
#include "operator_info.hpp"

namespace cdr
{
class Tasks
{

public:
    static void* addBillingTask(const size_t  a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_map);
    static void* updateBillingTask(const size_t  a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_map);
    static void* deleteBillingTask(const size_t  a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, BillingInfo>& a_map);
    static void* addOperatorTask(std::string const& a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_map);
    static void* updateOperatorTask(std::string const& a_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_map);
    // static void* linkGraphTask(const size_t  const& a_imsi, Cdr const& a_cdr, std::unordered_map<size_t, LinkGraphInfo>& a_map);

    
};

}//namespace cdr

#endif /*#ifndef PRODUCE_REPORT_HPP*/