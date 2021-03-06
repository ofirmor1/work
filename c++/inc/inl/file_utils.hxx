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

#include "utils.hpp"

namespace cpp
{

std::map<char, size_t> letterFrequency(std::ifstream& a_file)
{ 
    using namespace std;

    map<char, size_t> frequency;
    char c;
    while(a_file >> c && !a_file.fail())
    {
        if(isalpha(c))
        {
            ++frequency[std::tolower(c)];
        }
    }

    return frequency;
}

size_t countWords(std::istream& a_file, WordMap& a_words) 
{
    std::string s;

    while (a_file >> s) 
    {
        if(a_file.good())
        {
            ++a_words[s];
        }   
    }

    return a_words.size();
}  


std::vector<std::pair<std::string,size_t> > topNWords(std::ifstream& a_file, size_t k)
{
    //TODO: insertion sort if k is small, if k ~ totalWords -> reverse insertion
    using namespace std;

    WordMap w;
    size_t totalWords = countWords(a_file, w);

    if(k == totalWords)
    {
        vector<pair<string,size_t> > vec;
        vec.assign(w.begin(), w.end());
        return vec;
    }

    priority_queue<pair<string, size_t>, vector<pair<string,size_t> > , Comparator> v;

    map<string, size_t> :: iterator it = w.begin();

    for(; it != w.end(); ++it)
    {
        v.push(make_pair((*it).first, (*it).second));
    }

    vector<pair<string, size_t> > top;
    top.reserve(k);

    while(k > 0)
    {      
        top.push_back(v.top());
        v.pop();
        --k;
    }

    return top;
}

typedef std::pair<std::string const, size_t>* WordPair;
typedef std::pair<std::string const, size_t> WordPairInMap;
typedef std::priority_queue<WordPair, std::vector<WordPair>, GreaterPairCompare<std::string, size_t> > WordFrequencyHeap;

WordFrequencyHeap topNWords2(std::map<std::string, size_t>& a_map, size_t a_numWords)
{
    using std::vector;
    using std::map;
    using std::string;

    vector<WordPair> v;

    map<string, size_t>::iterator itr = a_map.begin();
    map<string, size_t>::iterator end = a_map.end();

    const size_t k = std::min(a_map.size(), a_numWords);
    v.reserve(k);

    for(size_t i = 0; i < k; ++i){
        WordPairInMap* w = &*itr;
        v.push_back(w);
        ++itr;
    }

    assert(v.size()==3);

    GreaterPairCompare<string, size_t> cmp;
    WordFrequencyHeap minHeap(cmp, v);

    assert(minHeap.size() == 3);
    
    while(itr != end)
    {
        WordPairInMap* w = &*itr;
        if( cmp(w, minHeap.top()))
        {
            minHeap.pop();          
            minHeap.push(w);    
        }

        ++itr;
    }
    
	return minHeap;
}

} // namespace cpp



#endif /*FILE_UTILS_HXX*/







