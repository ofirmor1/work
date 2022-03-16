#ifndef DIRECTORY_EXCEPTION_HPP
#define DIRECTORY_EXCEPTION_HPP

#include <stdexcept>

namespace mt
{
class DirectoryException : public std::logic_error 
{
public:
    explicit DirectoryException(const std::string& what_arg);
};

}//namespace mt


#endif/* DIRECTORY_EXCEPTION_HPP */