#include <stddef.h>
#include <stdio.h>
#include <string.h>

int isPalindrome(char* a_str)
{

    for(size_t i = 0, j = strlen(a_str) - 1; i < j; ++i, --j)
    {
        if(a_str[i] != a_str[j])
        {
            return -1;
        }
    }
    return 1;
}

int main()
{
    char* word = "hello";
    
    int res = isPalindrome(word);
    if (res == 1)
    {
        printf("the word |%s| is palindrome ", word);
    }
    else
    {
        printf("the word |%s| is not palindrome \n\n", word);
    }

    char* word2 = "abba";
    res = isPalindrome(word2);
    if (res == 1)
    {
        printf("the word |%s| is palindrome ", word2);
    }
    else
    {
        printf("the word |%s| is not palindrome ", word2);
    }

    return 0;
}