#include <stddef.h>
#include <stdio.h>
// #include <algorithm>


int removeDuplicates(int arr[], int n)
{
    if(n == 0 || n == 1)
    {
        return n;
    }

    int j = 0;
    for(int i = 0; i < n - 1; ++i)
    {
        if(arr[i] != arr[i+1])
        {
            arr[j++] = arr[i];
        }
    }

    arr[j++] = arr[n-1];

    return j;
}


int main()
{
    int arr[] = {1,2,3,4,4,4,4,5,5,5,6,9};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    arrSize = removeDuplicates(arr, arrSize);

    for(int i = 0;i < arrSize; ++i)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}