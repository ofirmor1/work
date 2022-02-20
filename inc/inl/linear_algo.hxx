#ifndef LINEAR_ALGO_HXX
#define LINEAR_ALGO_HXX

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
void Chaos(std::vector<T> &a_vec)
{
    generate(a_vec.begin(), a_vec.end(), RandomGenerator<T>(2,100));

}

template <typename T>
T sumElements(std::vector<T> &a_vec)
{
    T sum = 0;
    for (size_t i = 0; i < a_vec.size(); i++)
    {
        sum += a_vec[i];
    }

    return sum;
}

template <typename T>
T simpleSum(std::vector<T> &a_vec)
{
    T sum = 0;
    sum = std::accumulate(a_vec.begin(), a_vec.end(), 0.0);
    
    return sum;
}

template <typename T>
void oddsOut(std::vector<T> &a_vec)
{
    for (size_t i = 0; i < a_vec.size(); ++i)
    {
        if(a_vec[i] % 2 != 0)
        {
            a_vec.erase(a_vec.begin()+i);
            --i;
        }
    }   
}

template <typename T, typename F>
int findx(std::vector<T> const& a_vec, F a_cmp)  
{ 
    size_t index = 0;
    size_t value = a_vec[0];
    size_t const size = a_vec.size();
    for(size_t i = 0; i < size; i++)
    {
        if(a_cmp(a_vec[i], a_vec[index]))
        {
            index = i;
            value = a_vec[i];
        }
    }

    return value;
}

template<typename T>
std::pair<size_t, size_t> extremes(std::vector<T> const& a_vector)
{
    std::pair<size_t, size_t> minMax;

    if(a_vector.size() == 0)
    {
        minMax.first = a_vector.size();
        minMax.second = a_vector.size();
        return minMax;
    }

    minMax.first = findx(a_vector, std::less<size_t>());
    minMax.second = findx(a_vector, std::greater<size_t>());
    return minMax;
}

template<typename T>
size_t firstDuplicate(std::vector<T> const& a_vec)
{
	T item;
	size_t i,j;
    size_t end = a_vec.size();
	for(i = 0; i < end; ++i)
	{
		item = a_vec.at(i);

		for(j = i + 1; j < end; ++j)
		{
			if(item == a_vec.at(j))
			{
				return j;
			}
		}
	}

	return end;
}

template<typename T>
std::vector<int>::iterator findValueInVector(std::vector<T> &a_vec, T a_val)
{
    std::vector<int>::iterator it;
    it = std::find(a_vec.begin(), a_vec.end(), a_val);

    return it;
}

template<typename T>
size_t countCommontStrange(std::vector<T> &a_first, std::vector<T> &a_second, std::vector<T> &a_third)
{
    size_t commonValues = 0;

    for (std::vector<int>::iterator it = a_first.begin() ; it != a_first.end(); ++it)
    {
        if  ((findValueInVector(a_second, *it) != a_second.end()) &&
            !(findValueInVector(a_third, *it) != a_third.end())) 
        {
            ++commonValues;
        }
    }
    
    return commonValues;
}

#endif /*LINEAR_ALGO_HXX*/

} // namespace cpp






