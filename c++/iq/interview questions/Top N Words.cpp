#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <queue>
#include <iterator>
#include <cassert>


template<typename T, typename U>
struct GreaterPairCompare
{
      bool operator()(const std::pair<const T,U>* a,const std::pair<const T,U>* b) const
      {
            return a->second > b->second;
      }
};

typedef std::pair<std::string const, size_t>* WordPair;
typedef std::pair<std::string const, size_t> WordPairInMap;
typedef std::priority_queue<WordPair, std::vector<WordPair>, GreaterPairCompare<std::string, size_t> > WordFrequencyHeap;
WordFrequencyHeap topNWords3(std::map<std::string, size_t>& a_map, size_t a_numWords)
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

int main(){
    using std::map;
    using std::string;
    std::map<string, size_t> m;
    
    m["hello"] = 6;
    m["world"] = 2;
    m["mars"] = 1;
    m["C++"] = 9;
    m["Java"] = 3;
    m["Fortan"] = 7;
    assert(m.size() == 6);

    WordFrequencyHeap r = topNWords3(m, 3);
    assert(r.size() == 3);
    std::cout << r.size() << '\n';
    
    for(size_t i = 0; i < 3; ++i){
        WordPair f = r.top();
        std::cout << f->first << '\n';
        r.pop();
    }
}
