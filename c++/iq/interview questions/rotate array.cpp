#include <iostream>
#include <cstddef>

//n - arrsize
//k - num of rotates

void rotateArr(int *arr, size_t n, size_t k)
{
    // int arr1[] = {1, 3, 4, 5, 7, 9, 12, 14};
    // int arr2[] = {2, 6, 11, 15};
    // 5 6 7 9 11 12 14 15
    std::cout << arr1[n-1] << " \n";
    std::cout << arr2[k-1] << " \n";
    size_t j = 0;
    for (size_t i = n-1; i > 0 && k > 0; --i)
    {
        arr[i] = arr[j]
        {
            arr1[i] = arr2[k-1] + arr1[i];
            arr2[k-1] = arr1[i] - arr2[k-1];
            arr1[i] = arr1[i] - arr2[k-1];
        }        
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int arr[] = {1, 3, 4, 5, 7, 9, 12, 14};
    size_t n = *(&arr + 1) - arr;
    size_t k = 1;
    rotateArr(arr, n, k);

    for(size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}
