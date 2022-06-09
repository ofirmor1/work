#include "processor.hpp"
#include "database.hpp"
#include "directory_reader.hpp"
#include <algorithm>
#include <fstream>

namespace cdr
{

Processor::Processor()
: m_parser()
{}

Processor::~Processor()
//TODO : STOP THREADS FROM RUNNIG
//       SAVE WHATS DONE UNTIL THIS POINT
{

}
// void updateData()
// {

// }

void Processor::Process() {
    std::vector<Cdr> newCdrsVec;
    std::string dirofNewFiles("data_base/new_files");
    std::string dirofDoneFiles("data_base/finished_files");
    mt::DirectoryReader processingDirectory(dirofNewFiles);
    mt::DirectoryReader doneDirectory(dirofDoneFiles);
    std::vector<std::string> vec = processingDirectory.files();
    while(!(vec.empty()))
    { 
        newCdrsVec = m_parser.fileParser(dirofNewFiles + "/" + processingDirectory.GetName());
        for(size_t i = 0; i < newCdrsVec.size(); ++i) 
        {
            addNewCdr(newCdrsVec.at(i));
            m_database->add(std::to_string(newCdrsVec.at(i).m_imsi), newCdrsVec.at(i));
        }

        std::ofstream doneFile(dirofDoneFiles + "/" + doneDirectory.GetName());
        std::ifstream currCdrFile(dirofNewFiles + "/" + processingDirectory.GetName());

        dirofDoneFiles << currCdrFile.rdbuf();

        std::remove((dirofNewFiles + "/" + processingDirectory.GetName()).c_str());
    }
}

void Processor::addNewCdr(Cdr& a_newCdr) 
{
    if(m_imsiMap.find(a_newCdr.m_msisdn) == m_imsiMap.end()) 
    {
        m_imsiMap[a_newCdr.m_msisdn] = a_newCdr.m_imsi;
    }
}

}// namespace cdr