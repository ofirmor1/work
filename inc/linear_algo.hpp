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

using namespace std;

template <typename T>
void Chaos(vector<T> &a_vec)
{
    generate(a_vec.begin(), a_vec.end(), RandomGenerator<T>(2,100));

}

template <typename T>
T sumElements(vector<T> &a_vec)
{
    T sum = 0;
    for (size_t i = 0; i < a_vec.size(); i++)
    {
        sum += a_vec[i];
    }

    return sum;
}


template <typename T>
T simpleSum(vector<T> &a_vec)
{
    T sum = 0;
    sum = accumulate(a_vec.begin(), a_vec.end(), 0.0);
    
    return sum;
}

template <typename T>
void oddsOut(vector<T> &a_vec)
{
    for (size_t i = 0; i < a_vec.size(); i++)
    {
        if(a_vec[i] % 2 == 0)
        {
            a_vec.erase(a_vec.begin()+i);
        }
    }   
}

pair<int, int> extremes(vector<int> &a_vec)
{
    int minVal = a_vec[0];
    int maxVal = a_vec[0];
    for (size_t i = 0; i < a_vec.size(); i++)
    {
        if(a_vec[i] < minVal)
        {
            minVal = a_vec[i];
        }
        if(a_vec[i] > maxVal)
        {
            maxVal = a_vec[i];
        }
    }

    return make_pair(minVal, maxVal);
}



#endif /*LINEAR_ALGO_HPP*/

} // namespace cpp






