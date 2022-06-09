#include "quest.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>

namespace iq
{

template<typename T>
void swap(T& a_first, T& a_second)
{
    a_first = a_first + a_second;
    a_second = a_first - a_second;
    a_first = a_first - a_second;

}
//q1
void mergeArr(int* a_arr1, int* a_arr2, size_t n, size_t k)
{
    for (size_t i = n-1; i > 0; --i)
    {
        if(a_arr1[i] < a_arr2[k-1])
        {
            swap(a_arr1[i], a_arr2[k-1]);
        }
        std::sort(a_arr2, a_arr2 + k);      
    }
    a_arr1[0] = a_arr2[k-1];
}

//q2
static void rotateByOne(int* a_arr, size_t n)
{
    int temp = a_arr[n-1];
    for (size_t i = n-1; i > 0; --i)
    {
        a_arr[i] = a_arr[i-1];
    }
    a_arr[0] = temp;
}

void rotateArr(int* a_arr, size_t n, size_t k)
{
    for(size_t i = 0; i < k; ++i)
    {
        rotateByOne(a_arr, n);
    }
}

//q3
void replaceEachElmWIthLargestOnRight(int* a_arr, int n)
{
    if(n == 1)
    {
        return;
    }
    
    for (int i = 0; i < n-1; ++i)
    {
        int max = 0;
        for(int j = i+1; j <= n-1; ++j)
        {
            if(a_arr[j] > max)
            {

                max = a_arr[j];
            }
        }
        a_arr[i] = max;
    }
}

//q4
void replaceEachElmWIthClosestLargestOnRight(int* a_arr, int n)
{
    if(n == 1)
    {
        return;
    }
    
    for (int i = 0; i <= n-1; ++i)
    {
        int max = -1;
        for(int j = i+1; j <= n-1; ++j)
        {
            if(a_arr[j] > a_arr[i])
            {
                max = a_arr[j];
                break;
            }
        }
        a_arr[i] = max;
    }
}

//q5
static bool isPrime(size_t n)
{
    if(n == 0 || n == 1)
    {
        return false;
    }
    for (size_t i = 2; i <= n / 2; ++i)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int* nFirstPrime(size_t n, int* a_arr)
{
    size_t count = 0;
    size_t i = 2;
    while(count < n)
    {
        if(isPrime(i))
        {
            a_arr[count] = i;
            ++count;
        }
        ++i;
    }
    return a_arr;
}

//q6
void sortArr(int* a_arr, size_t n)
{
    size_t i, countMinusOnes = 0, countZeros = 0, countOnes = 0;

    for (i = 0; i < n; i++) 
    {
        switch (a_arr[i]) 
        {
        case -1:
            countMinusOnes++;
            break;
        case 0:
            countZeros++;
            break;
        case 1:
            countOnes++;
            break;
        }
    }
    
    i = 0;
    while (countMinusOnes > 0)
    {
        a_arr[i++] = -1;
        --countMinusOnes;
    }

    while (countZeros > 0)
    {
        a_arr[i++] = 0;
        --countZeros;
    }
 
    while (countOnes > 0)
    {
        a_arr[i++] = 1;
        --countOnes;
    }
}

//q6
void sortArr2(std::vector<int>& a_vec, size_t n)
{
    size_t count[3] = {0,0,0};

    std::for_each(a_vec.begin(), a_vec.end(), [&count](int e){++count[e+1];});

    auto from = &a_vec[0];
    auto to = from + count[0];
    std::fill(from,to,-1);

    from = to;
    to = from + count[1];
    std::fill(from,to,0);

    from = to;
    to = from + count[2];
    std::fill(from,to,1);   

}

//q7
int numOfSetBits(int n)
{
    size_t count = 0;   
    while(n)
    {
        count += n & 1;
        n >>= 1;
    }

    return count;
}

//q7 with LUT
int LUT[256];
void SetBitsLUT()
{
    for (size_t i = 0; i < 256; ++i)
    {
        LUT[i] = (i & 1) + LUT[i / 2];
    }
}

int numOfSetBitsLUT(int n)
{
    SetBitsLUT();
    return (LUT[n & 0xff]
        + LUT[(n>>8) & 0xff]
        + LUT[(n>>16) & 0xff]
        + LUT[n>>24]);
}

//q8
int numOfPairSetBits(int n)
{
    size_t count = 0;
    while(n)
    {
        if(n & 1 && ((n >>= 1) & 1))
        {
            ++count;
        }
        n >>= 1 & 1;
        printf("%d ", n);
    }
    return count;
}

//q8 with LUT
int pairLUT[256];
void pairSetBitsLUT()
{
    for (size_t i = 0; i < 256; ++i)
    {
        pairLUT[i] = (i & 1) & ((i >> 1) & 1);
    }
}

int numOfPairSetBitsLUT(int n)
{
    pairSetBitsLUT();
    return (pairLUT[n & 0xff]
        + pairLUT[(n>>8) & 0xff]
        + pairLUT[(n>>16) & 0xff]
        + pairLUT[n>>24]);
}
 
}//namespace iq


