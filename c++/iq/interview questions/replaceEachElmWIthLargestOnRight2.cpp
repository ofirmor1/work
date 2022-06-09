#include <iostream>
#include <cstddef>

//n - arrsize
//k - num of rotates

void printArr(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}

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
        };
        arr[i] = max;
    }
}

int main()
{
    int arr[] = {5, 2, 0, 7, 9, 5, 2, 7};
    int n = *(&arr + 1) - arr;

    replaceEachElmWIthLargestOnRight(arr, n);

    printArr(arr, n);
    
    return 0;
}
