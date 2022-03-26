#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../cdr.hpp"
#include "../billing_info.hpp"
#include "../operator_info.hpp"
#include <string>
#include <memory> 

namespace cdr 
{

class Database 
{
public:
    enum InfoType 
    { 
        BILLING,
        OPERATOR,
        LINKGRAPH 
    };

    Database();
    virtual ~Database() = 0;

    virtual bool add(std::string const& a_query, Cdr& a_cdr) = 0;
    virtual bool update(std::string const& a_query, Cdr& a_cdr) = 0;
    virtual bool deleteObj(std::string const& a_query , InfoType a_type) = 0;    

    virtual void* get(std::string const& a_query, InfoType a_type) = 0;

private:
    std::unordered_map<size_t, BillingInfo> m_billingMap;
    std::unordered_map<std::string, OperatorInfo> m_operatorSettlementMap; 
    // std::unordered_map<size_t, LinkGraphInfo> m_linksGraphMap;
};

} // cdr

#endif // DATABASE_HPP