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
int* nFirstPrime(int n, int* arr)
{
    size_t count = 1;
    size_t i, j = 2;
    while(count <= n)
    {
        for (int i = 1; i <= n; ++i)
        {
    }

    
        while(isPrime(j++))
        {
            if(isPrime(j))
            {
                arr[i] = j;
            } 
        }    
    }
    return arr;
}

int main()
{
    int n = 3;
    int arr[n];
    int* result = nFirstPrime(n, arr);
    printArr(result, n);
    
    return 0;
}
