#include "quest.hpp"
#include <algorithm>

namespace iq
{

//q1
void mergeArr(int *arr1, int *arr2, size_t n, size_t k)
{
    for (size_t i = n-1; i > 0; --i)
    {
        if(arr1[i] < arr2[k-1])
        {
            arr1[i] = arr1[i] + arr2[k-1];
            arr2[k-1] = arr1[i] - arr2[k-1];
            arr1[i] = arr1[i] - arr2[k-1];
        }
        std::sort(arr2, arr2 + k);      
    }
    arr1[0] = arr2[k-1];
}

//q2
static void rotateByOne(int *arr, size_t n)
{
    int temp = arr[n-1];
    for (size_t i = n-1; i > 0; --i)
    {
        arr[i] = arr[i-1];
    }
    arr[0] = temp;
}

void rotateArr(int *arr, size_t n, size_t k)
{
    for(size_t i = 0; i < k; ++i)
    {
        rotateByOne(arr, n);
    }
}

//q3
void replaceEachElmWIthLargestOnRight(int *arr, int n)
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
            if(arr[j] > max)
            {

                max = arr[j];
            }
        }
        arr[i] = max;
    }
}

//q4
void replaceEachElmWIthClosestLargestOnRight(int *arr, int n)
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
            if(arr[j] > arr[i])
            {
                max = arr[j];
                break;
            }
        }
        arr[i] = max;
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

int* nFirstPrime(size_t n, int* arr)
{
    size_t count = 0;
    size_t i = 2;
    while(count < n)
    {
        if(isPrime(i))
        {
            arr[count] = i;
            ++count;
        }
        ++i;
    }
    return arr;
}

//q6
void sortArr(int* arr, size_t n)
{
    size_t i, countMinusOnes = 0, countZeros = 0, countOnes = 0;

    for (i = 0; i < n; i++) 
    {
        switch (arr[i]) 
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
        arr[i++] = -1;
        countMinusOnes--;
    }

    while (countZeros > 0)
    {
        arr[i++] = 0;
        countZeros--;
    }
 
    while (countOnes > 0)
    {
        arr[i++] = 1;
        countOnes--;
    }
}
 
}//namespace iq


