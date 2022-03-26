#include "directory_exception.hpp"
#include "directory_reader.hpp"

namespace mt
{
DirectoryReader::DirectoryReader(std::string a_path)
: m_dir(opendir(a_path.c_str())) 
{
  if (m_dir == NULL) 
  {
    throw DirectoryException("Can't open directory");
  }
}

DirectoryReader::~DirectoryReader() 
{
  closedir(m_dir);
}

std::vector<std::string> DirectoryReader::files() const 
{
    std::vector<std::string> files;
    struct dirent *ent;
    while ((ent = readdir(m_dir)) != NULL) 
    {
        if (ent->d_type == DT_REG) 
        {
            files.push_back(ent->d_name);
        }
    }

    return files;
}

std::string  DirectoryReader::getName() const 
{
  return std::string(this->m_dirEntry->d_name); 
}


}//namespace mt