#include <cstdio>

void swap(void * a, void * b)
{
    int* x = (int*)a;
    int* y = (int*)b;
    if(x != y)
    {
        *x^=*y;
        *y^=*x;
        *x^=*y;
    }
}

int main()
{
    int a = 10;
    int b = 20;
    printf("%d %d ", a, b);
    swap (&a,&b);
    printf("\n%d %d ", a, b);
}