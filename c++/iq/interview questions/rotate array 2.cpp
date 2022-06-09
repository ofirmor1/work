#include <iostream>
#include <cstddef>

//n - arrsize
//k - num of rotates

void rotateByOne(int *arr, size_t n)

void rotateArr(int *arr, size_t n, size_t k)
{
    size_t j = 0;
    int temp = arr[i];
    for (size_t i = n-1; i > 0; --i)
    {
        
        
        arr[i] = arr[i] + arr[j];
        arr[j] = arr[i] - arr[j];
        arr[i] = arr[i] - arr[j];
        ++j;
        --k;
    }
    }
    
    std::cout << std::endl;
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
