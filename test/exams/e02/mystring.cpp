#include "mystring.hpp"
#include <string>

namespace cpp
{
// hello   123456
// elloh   456123
using namespace std;
bool isReversed(string a_str1, string a_str2)
{
    size_t size1 = a_str1.length();
    size_t size2 = a_str2.length();

    if(size1 != size2)
    {
        return false;
    }

    string s = a_str1 + a_str1;
    size_t found = s.find(a_str2);
    return (found != string::npos) ? true: false;
}

}//namespace cpp
