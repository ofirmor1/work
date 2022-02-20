#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <map>

namespace cpp
{

using std::string;   
using std::map;  
using std::pair;

map<char, int> letterFrequency(const char* a_filename);

bool cmp(pair <string, int> a_firstPair, pair <string, int> a_secondPair);

} // namespace cpp

#include "./inl/file_utils.hxx"

#endif /*FILE_UTILS_HPP*/





