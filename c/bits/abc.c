#include <stdio.h>
#include <math.h>

typedef void(*selector)(char*, double);

int main()
{
    printf("%f", selector("sinus")(PI/2));
}








