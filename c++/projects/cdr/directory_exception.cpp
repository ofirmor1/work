#include "directory_exception.hpp"

namespace mt
{
    DirectoryException::DirectoryException(std::string const& what_arg)
    : std::logic_error(what_arg) {}
} //namespace mt
