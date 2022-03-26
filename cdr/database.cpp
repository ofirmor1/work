#include "database.hpp"
#include "directory_reader.hpp"
#include "../billing_aggregator.hpp"
#include "../operator_aggregator.hpp"
#include "../tasks.hpp"
#include "../cdr.hpp"
#include <cstddef>
#include <vector>

namespace cdr
{
Database::Database()
: m_billingMap()
, m_operatorSettlementMap()
{}

bool Database::add(std::string const& a_query, Cdr& a_cdr)
{
    void* billing = Tasks::addBillingTask(std::stoul(a_query), a_cdr, this->m_billingMap);
    void* Operator = Tasks::addOperatorTask(a_query, a_cdr, this->m_operatorSettlementMap);
    // void* linkGraph = Tasks::linkGraphTask(a_query, a_cdr, this->m_linkGraphMap);

    std::vector<void*> v;
    v.push_back(billing);
    v.push_back(Operator);
    // v.push_back(linkGraph);

    return true;
}

bool Database::update(std::string const& a_query, Cdr& a_cdr)
{
    void* billing = Tasks::updateBillingTask(std::stoul(a_query), a_cdr, this->m_billingMap);
    void* Operator = Tasks::updateOperatorTask(a_query, a_cdr, this->m_operatorSettlementMap);
    // void* linkGraph = Tasks::linkGraphTask(a_query, a_cdr, this->m_linkGraphMap);

    std::vector<void*> v;
    v.push_back(billing);
    v.push_back(Operator);
    // v.push_back(linkGraph);

}

bool Database::deleteObj(std::string const& a_query, InfoType a_type)
{
    switch (a_type)
    {
        case BILLING:
            m_billingMap.erase(std::stoul(a_query));
            break;
        
        case OPERATOR:
            m_operatorSettlementMap.erase(a_query);
            break;

        // case LINKGRAPH:
        //     m_linksGraphMap.erase(std::stoul(a_query));
        //     break;   
    }
}

void* Database::get(std::string const& a_query, InfoType a_type)
{
    switch (a_type)
    {
        case BILLING:
            return &m_billingMap.at(std::stoul(a_query));
            break;
        
        case OPERATOR:
            return &m_operatorSettlementMap.at(a_query);
            break;
            
        // case LINKGRAPH:
        //     return &m_linksGraphMap.at(std::stoul(a_query));
        //     break;
    }
}



}//namespace cdr
