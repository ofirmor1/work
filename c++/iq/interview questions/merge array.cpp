#include <iostream>
#include <cstddef>

void mergeArr(int *arr1, int *arr2, size_t n, size_t k)
{
    // int arr1[] = {1, 3, 4, 5, 7, 9, 12, 14};
    // int arr2[] = {2, 6, 11, 15};
    for (size_t i = n; i > 0; --i)
    {
        if(arr2[k] < arr2[k-1])
        {
            arr2[k] = arr2[k] + arr2[k-1];
            arr2[k-1] = arr2[k] - arr2[k-1];
            arr2[k] = arr2[k] - arr2[k-1];
            --k;
        }
        std::cout << arr2[k] << " \n";
        if(arr1[i] < arr2[k])
        {
            arr1[i] = arr2[k] + arr1[i];
            arr2[k] = arr1[i] - arr2[k];
            arr1[i] = arr1[i] - arr2[k];
        }
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int arr1[] = {1, 3, 4, 5, 7, 9, 12, 14};
    int arr2[] = {2, 6, 11, 15};
    size_t n = *(&arr1 + 1) - arr1;
    size_t k = *(&arr2 + 1) - arr2;
    mergeArr(arr1, arr2, n, k);

    for(size_t i = 0; i < n; i++)
    {
        std::cout << arr1[i] << " ";
    }
    return 0;
}
