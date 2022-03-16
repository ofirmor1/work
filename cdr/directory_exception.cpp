#include "directory_exception.hpp"

namespace mt
{
    DirectoryException::DirectoryException(const std::string& what_arg)
    : std::logic_error(what_arg) {}
} //namespace mt
