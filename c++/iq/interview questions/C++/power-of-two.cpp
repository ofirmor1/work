#include <iostream>

int numOfBitsOnInNum(size_t num)
{
    int count = 0;
    while(num)
    {
        ++count;
        num = num >> 1;
    }

    return count;
}

bool isPowerOfTwo(size_t num)
{
    int numofBits = numOfBitsOnInNum(num);
    while((numofBits-1) > 0)
    {
        int isBitOn = num & 1;
        if(isBitOn)
        {
            return false;
        }
        --numofBits;
        num = num >> 1;
    }

    return true;
}

bool isPowerOfTwoRec(size_t num)
{
    if(num == 1)
    {
        return true;
    }
    else if(num % 2 != 0 || num == 0)
    {
        return false;
    }
    return isPowerOfTwoRec(num / 2);
}

bool isAdivededByB(int a, int b)
{
    if ((a < b) && isPowerOfTwoRec(a))
    {
        return true;
    }

    return false;
}

int main()
{
    bool res = isPowerOfTwo(32);
    std::cout << res << std::endl;

    res = isPowerOfTwoRec(32);
    std::cout << res << std::endl;

    res = isAdivededByB(16, 32);
    std::cout << res << std::endl;

    res = isAdivededByB(32, 8);
    std::cout << res << std::endl;

}