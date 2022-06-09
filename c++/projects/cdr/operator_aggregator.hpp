#ifndef OPERATOR_AGGREAGATOR_HPP
#define OPERATOR_AGGREAGATOR_HPP

#include "cdr.hpp"
#include "operator_info.hpp"
#include <unordered_map>


namespace cdr
{

class OprAggr
{
public:
    OprAggr(std::string const& m_mccmnc, Cdr const& a_cdr, std::unordered_map<std::string, OperatorInfo>& a_mapOfOperators);

    void newOperator();

    void updateOperator(OperatorInfo& a_operator) const;

private:
    std::string m_mccmnc;
    Cdr m_cdr;
    std::unordered_map<std::string, OperatorInfo>& m_mapOfOperators;
    
};

}//namespace cdr

#endif /*#ifndef OPERATOR_AGGREAGATOR_HPP*/