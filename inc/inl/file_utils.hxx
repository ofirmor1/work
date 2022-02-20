#ifndef FILE_UTILS_HXX
#define FILE_UTILS_HXX

#include <iostream>
#include <fstream>
#include <cctype>
#include <cassert>
#include <string>
#include <map>
#include <iterator>
#include <queue>

namespace cpp
{

using std::string;   
using std::map;  
using std::pair;

map<char, int> letterFrequency(const char* a_filename)
{
    std::fstream book;
	book.open(a_filename, std::ios::in);
	assert(!book.fail());

    map<char, int> frequency;
    char oneChar;
    oneChar = book.get();
    while(!book.eof())
    {
        if(oneChar != ' ')
        {
            ++frequency[oneChar];
        }
        oneChar = book.get();
    }

    book.close();
    
    return frequency;
}

struct Comparator
{
    bool operator()(pair <string ,int> a, pair <string, int> b)
    {
        if(a.second != b.second) 
            return !(a.second < b.second);
        return !(a.first > b.first);
    }
};

bool cmp(pair <string, int> a_firstPair, pair <string, int> a_secondPair)
{
    if(a_firstPair.second != a_secondPair.second)
    {
        return a_firstPair.second > a_secondPair.second;
    } 
        
    return a_firstPair.first < a_secondPair.first;
}

} // namespace cpp

// using map to map the wrods in file, and priority_queue to find the k most frequent.
// void topNWords(const char* a_filename, int a_top)
// {
// 	std::ifstream book(a_filename);
// 	assert(!book.fail());
// }

#endif /*FILE_UTILS_HXX*/







