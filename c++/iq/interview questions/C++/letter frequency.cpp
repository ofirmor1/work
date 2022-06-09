#include <iostream>
#include<stdlib.h>
#include <string>

void letterFrequancy(std::string a_str)
{
    int arr[26] = {0};

    for(int i = 0; i < a_str.length(); ++i)
    {
        arr[a_str[i] - 'a']++;
    }

    for(int i = 0; i < 26; ++i)
    {
        if(arr[i])
        {
            std::cout << "letter " << char('a' + i) << " appears " << arr[i] <<
            "times" << std::endl;
        }
    }
}

int main()
{
    std::string str = "hello world";
    std::cout << "frequency of letters: "<< str << std::endl;
    letterFrequancy(str);

    
}