#ifndef LINEAR_ALGO_HXX
#define LINEAR_ALGO_HXX

#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <numeric>
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
bool findValueInVector(std::vector<T> const& a_vec, T a_val)
{
    return std::find(a_vec.begin(), a_vec.end(), a_val) != a_vec.end();
}

template<typename T>
size_t countCommontStrange(std::vector<T> const& a_first, std::vector<T> const& a_second, std::vector<T> const& a_third)
{
    size_t count = 0;

    for (std::vector<int>::const_iterator it = a_first.begin() ; it != a_first.end(); ++it)
    {
        if  (findValueInVector(a_second, *it) &&
            !findValueInVector(a_third, *it))
        {
            ++count;
        }
    }
    
    return count;
}

template<typename T>
size_t countCommontStrange2(std::vector<T> const& a_first, std::vector<T> const& a_second, std::vector<T> const& a_third)
{
    std::set<T const*, CompareByPointer<T> > c;

    for (size_t i = 0; i < a_second.size(); ++i)
    {
        c.insert(&a_second[i]);
    }
    
    for (size_t i = 0; i < a_third.size(); ++i)
    {
        c.erase(&a_third[i]);
    }

    size_t count = 0;

    size_t size = a_first.size();

    for (size_t i = 0; i < size; ++i)
    {
        count += c.count(&a_first[i]);
    }

    return count;
}

template<typename T>
int findFirstUnique(std::vector<T> const& a_vec)
{
    std::map<T, int> uniqMap;
    std::vector<int>::const_iterator it;
    std::pair<typename std::map<T, int>::iterator, bool> ret;

    for (it = a_vec.begin(); it != a_vec.end(); ++it)
    {
        ret = uniqMap.insert(std::pair<T, int>(*it, 1));

        if(ret.second == false)
        {
            uniqMap.erase((*it));
            uniqMap.insert(std::pair<T,int>(*it, -1));
        }
    }

    for (size_t i = 0; i < a_vec.size(); i++)
    {
        if(uniqMap[a_vec[i]] == -1)
        {
            return i;
        }
    }

    return -1;    
}

#endif /*LINEAR_ALGO_HXX*/

} // namespace cpp

