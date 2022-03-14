#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include<pthread.h>
#include "sub_processor.hpp"
#include "opr_processor.hpp"

namespace cdr
{

class Processor 
{

public:
    Processor();
    
    void updateData();
    SubPro& getSub(Processor const& a_cur);
    OprPro& getOpr(Processor const& a_cur);

    void CreateThreads(Processor const& a_pro, size_t a_threads);

private:
    SubPro& m_subPro;
	OprPro& m_oprPro;
    // std::map<key, std::pair<mt::Mutex, std::map<(key % 10),SubPro> > > Hash;
};

}//namespace cdr

#endif /*#ifndef PROCESSOR_HPP*/