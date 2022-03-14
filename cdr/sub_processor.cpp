#include "sub_processor.hpp"

namespace cdr
{

size_t hashFunc(std::string a_msisdn)
{
    size_t n = std::stoi(a_msisdn);
    return (n * 17 << 8) ^ (n >> 7);
}

// size_t i = hashFunc(key) % capacity;
    

}//namespace cdr