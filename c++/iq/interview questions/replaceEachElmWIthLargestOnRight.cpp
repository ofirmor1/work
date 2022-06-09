#include <iostream>
#include <cstddef>

//n - arrsize
//k - num of rotates

void replaceEachElmWIthLargestOnRight(int *arr, size_t n)
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

int main()
{
    int arr[] = {1, 3, 4, 5, 7, 9, 12, 14};
    size_t n = *(&arr + 1) - arr;
    size_t k = 2;
    rotateArr(arr, n, k);

    for(size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}
