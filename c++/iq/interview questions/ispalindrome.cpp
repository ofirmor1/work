#include <string>
#include <iostream>

bool isPalindrome(std::string str)
{
    if(str.length() == 1)
    {
        return true;
    }
    int length = str.length() - 1;
    for(int i = 0, j = length; i < j; ++i, --j)
    {
        if(str[i] != str[j])
        {
            return false;
        }
        std::swap(str[i], str[j]);
    }
    return true;
}

bool isPalindromeReq(std::string str, int from, int to)
{
    if(from == to)
    {
        return true;
    }
    if(str[from] != str[to])
    {
        return false;
    }
    if(from < to + 1)
    {
        isPalindromeReq(str, from+1, to-1);
    }

    return true;
}

bool isPalReq(std::string str)
{
    int end = str.length() - 1;

    if(end == 0)
    {
        return true;
    }

    return isPalindromeReq(str, 0, end);
}

int main()
{
    std::string str = "ababa";
    auto res = isPalindrome(str);
    if(res == 1)
    {
        std::cout << "is palindrome\n" << std::endl;
    }
    if(res == 0)
    {
        std::cout << "is not palindrome\n" << std::endl;
    }

    res = isPalReq(str);
    if(res == 1)
    {
        std::cout << "is palindrome" << std::endl;
    }
    if(res == 0)
    {
        std::cout << "is not palindrome" << std::endl;
    }
}