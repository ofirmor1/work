#ifndef OPR_PROCESSOR_HPP
#define OPR_PROCESSOR_HPP

#include <map>
#include "operator.hpp"

namespace cdr
{

class OprPro : public Subscriber
{
public:

private:
    // std::map<key, std::pair<mt::Mutex, std::map<(key % 10),SubPro> > > Hash;
};

}//namespace cdr

#endif /*#ifndef OPR_PROCESSOR_HPP*/