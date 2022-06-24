#include <iostream>
#include <string>

std::string reverseString(std::string& s)
{
    for(int i = 0, j = s.length() - 1; i < j; ++i, --j)
    {
        std::swap(s[i], s[j]);
    }
    return s;
} 

int main()
{
    std::string s = "abc";
    std::cout << "before: " << s << std::endl;
    s = reverseString(s);
    std::cout << "after: " << s << std::endl;
}
