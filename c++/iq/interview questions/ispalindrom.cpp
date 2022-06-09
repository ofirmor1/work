#include <cstdlib>
#include <cstring>
#include <cstdio>

bool isPalindrom(char const* a_word)
{
    size_t size = strlen(a_word);
    for(size_t i = 0; i < size; i++)
    {
        if(a_word[0] != a_word[size-1])
            return false;
    }
    return true;
}

int main()
{
    char const* word = "abcdefgfedcba";
    bool res = isPalindrom(word);
    if(res)
    {
        printf("the word |%s| is palindrom", word);
    }
    else
        printf("the word |%s| is not palindrom", word);
    return 0;
}