#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <map>

typedef std::map<std::string, size_t> wordMap;

namespace cpp
{

std::map<char, size_t> letterFrequency(std::ifstream &a_file);

} // namespace cpp

#include "./inl/file_utils.hxx"

#endif /*FILE_UTILS_HPP*/





