#include <iostream>
#include <string>

bool rotatedStrings(std::string& s1, std::string& s2)
{
    if(s1.length() != s2.length())
    {
        return false;
    }

    std::string temp = s1 + s1;
    return temp.find(s2) != std::string::npos;
} 

int main()
{
    std::string s1 = "abc";
    std::string s2 = "cab";
    bool res = rotatedStrings(s1,s2);
    std::cout << res << std::endl;
}
