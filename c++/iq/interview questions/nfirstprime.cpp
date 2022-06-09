#include <iostream>
#include <cstddef>

void printArr(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}

bool isPrime(size_t n)
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
//  int n, count=1, flag, i=2, j;
//  while(count <= n)
// 	 {
// 		  flag = 0;
// 		  for(j=2; j <= i/2; j++)
// 		  {
// 			   if(i%j==0)
// 			   {
// 			    flag=1;
// 			    break;
// 			   }
// 		  }
// 		  if(flag==0)
// 		  {
// 			   printf("%d\t",i);
// 			   count++;
// 		  }
// 		  i++;
// 	 }
void nFirstPrime(size_t n, int* arr)
{
    int flag = 0;
    size_t count = 1;
    size_t i = 2;
    while(count <= n)
    {
        for (size_t j = 2; j <= i/2; ++j)
        {
            if(i % j == 0)
            {
                flag=1;
                break;
            }
        }
        
        if(flag==0)
        {
            printf("%ld\t",i);
            count++;
        }
        i++;
    }
    // return arr;
}

int main()
{
    size_t n = 3;
    int arr[n];
    nFirstPrime(n, arr);
    // int* result = nFirstPrime(n, arr);
    // printArr(result, n);
    
    return 0;
}
