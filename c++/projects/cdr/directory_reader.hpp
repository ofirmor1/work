#ifndef DIRECTORY_READER_HPP
#define DIRECTORY_READER_HPP

#include <dirent.h>
#include <vector>
#include <string>

namespace mt
{
class DirectoryReader 
{
public:
    explicit DirectoryReader(std::string a_path);
    ~DirectoryReader();
    
    std::vector<std::string> files() const;

    operator bool(){return bool(this->m_dirEntry);};
    std::string getName() const;

private:
    struct dirent* m_dirEntry;
    DIR* m_dir;
};

}//namespace mt



#endif  /* DIRECTORY_READER_HPP */