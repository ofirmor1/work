#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include<pthread.h>
#include<unordered_map>
#include "sub_processor.hpp"
#include "opr_processor.hpp"
#include "cdr.hpp"

namespace cdr
{

class Processor 
{

public:
    Processor();
    
    void updateData();
    SubPro& getSub(Processor const& a_cur);
    OprPro& getOpr(Processor const& a_cur);

    void addNewCdr(CdrLine& a_newCdr);

    void CreateThreads(Processor const& a_pro, size_t a_threads);

private:
    void Process();

private:
    // SubPro& m_subPro;
	// OprPro& m_oprPro;
    Cdr m_parser;
    std::unordered_map<std::string, size_t> m_imsiMap; 
};

}//namespace cdr

#endif /*#ifndef PROCESSOR_HPP*/