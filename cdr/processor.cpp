#include "processor.hpp"

namespace cdr
{
Processor::Processor()
{}

void updateData()
{

}

SubPro& Processor::getSub(Processor const& a_cur)
{
    return *this;
}

OprPro& Processor::getOpr(Processor const& a_cur)
{
    return *this;
}
}// namespace cdr