#ifndef PARA_ALGO_HPP
#define PARA_ALGO_HPP

#include <vector>
#include <cstddef>
#include <stddef.h>

namespace cpp
{

size_t sumVector(std::vector<int> const& a_vec, size_t a_numOfThreads);

}//namespace cpp

#include "./inl/para_algo.hxx"

#endif /*#ifndef PARA_ALGO_HPP*/