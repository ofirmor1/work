#include "processor.hpp"
#include "directory_reader.hpp"
#include <algorithm>

namespace cdr
{
// Processor::Processor()

// {}

// void updateData()
// {

// }

void Processor::Process() {
    std::vector<Cdr> newCdrs;
    std::string dirofNewFiles("data_base/new_files");
    std::string dirofDoneFiles("data_base/finished_files");
    mt::DirectoryReader processingDirectory(dirofNewFiles);
    std::vector<std::string> vec = processingDirectory.files();
    while(!(vec.empty()))
    { 
    }
}

void Processor::addNewCdr(CdrLine& a_newCdr) 
{
    if(m_imsiMap.find(a_newCdr.m_msisdn) == m_imsiMap.end()) 
    {
        m_imsiMap[a_newCdr.m_msisdn] = a_newCdr.m_imsi;
    }
}

}// namespace cdr