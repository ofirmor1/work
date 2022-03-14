#ifndef SUB_PROCESSOR_HPP
#define SUB_PROCESSOR_HPP

#include <map>
#include "subscriber.hpp"

namespace cdr
{

class SubPro : public Subscriber
{
public:
    SubPro();


    

private:
    Hash* m_subHash;
};

typedef MSISDN key;

size_t hashFunc(std::string a_msisdn);

}//namespace cdr

#endif /*#ifndef SUB_PROCESSOR_HPP*/