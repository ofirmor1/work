#include <stddef.h>
#include <iostream>
#include <string>

bool isPalindrome(std::string const& a_str)
{
    for(size_t i = 0, j = a_str.length() - 1; i < j; ++i, --j)
    {
        if(a_str[i] != a_str[j])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::string word = "hello";
    
    bool res = isPalindrome(word);
    if (res)
    {
        std::cout << "the word |" <<  word << "| is palindrome " << std::endl;
    }
    else
    {
       std::cout << "the word |" <<  word << "| is not palindrome " << std::endl;
    }

    std::string word2 = "abba";
    res = isPalindrome(word2);
    if (res)
    {
        std::cout << "the word |" <<  word2 << "| is palindrome " << std::endl;
    }
    else
    {
        std::cout << "the word |" <<  word2 << "| is not palindrome " << std::endl;
    }

    return 0;
}