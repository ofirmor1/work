#ifndef LINEAR_ALGO_HPP
#define LINEAR_ALGO_HPP

#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include "ball.hpp"
#include "utils.hpp"
	
namespace cpp
{

template <typename T>
void Chaos(std::vector<T> &a_vec);

template <typename T>
T sumElements(std::vector<T> &a_vec);

template <typename T>
T simpleSum(std::vector<T> &a_vec);

template <typename T>
void oddsOut(std::vector<T> &a_vec);

template <typename T>
std::pair<size_t, size_t> extremes(std::vector<T> const& a_vec);

template <typename T>
std::pair<size_t, size_t> extremes2(std::vector<T> const& a_vec);

template<typename T>
// size_t firstDuplicate(std::vector<T> const& a_vec);
size_t firstDuplicate(std::vector<T> const& a_vec);

} // namespace cpp  

#include "./inl/linear_algo.hxx"

#endif /*LINEAR_ALGO_HPP*/






