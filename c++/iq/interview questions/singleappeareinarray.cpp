
#include <cstdio>

int singleAppear(int* arr, int n)
{
    int elemTable[n] = {0};
    for(int i = 0; i < n; ++i)
    {
        ++elemTable[arr[i]];
    }

    for(int i = 0; i < n; ++i)
    {
        if(elemTable[arr[i]] == 1)
        {
            return arr[i];
        }
    }
    return -1;
}

int main()
{
    int arr[9] = {1,1,2,3,3,5,5,7,7};
    int res = singleAppear(arr, 9);
    printf("%d ", res);
}