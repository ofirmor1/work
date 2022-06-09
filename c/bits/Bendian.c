#include <stdio.h>
  
void show_mem_rep(char *start, int n) 
{
    int i;
    for (i = 0; i < n; i++)
         printf(" %.2d", start[i]);
    printf("\n");
}
  
int main()
{
   int i = 1;
   show_mem_rep((char *)&i, sizeof(i));
   getchar();
   return 0;
}
