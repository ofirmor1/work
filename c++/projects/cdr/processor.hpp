#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "cdr_parse.hpp"
#include "database.hpp"
#include<pthread.h>
#include<unordered_map>


namespace cdr
{

class Processor 
{

public:
    Processor();
    
    void updateData();
    void addNewCdr(Cdr& a_newCdr);

    void CreateThreads(Processor const& a_pro, size_t a_threads);

private:
    void Process();

private:
    CdrParse m_parser;
    std::shared_ptr<Database> m_database;
    std::unordered_map<std::string, size_t> m_imsiMap; 
};

}//namespace cdr

#endif /*#ifndef PROCESSOR_HPP*/