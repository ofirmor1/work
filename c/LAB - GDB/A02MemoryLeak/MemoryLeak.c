#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main ()
{
	char * kuku=NULL;
	for (int i=0;i<100;i++)
    {
	    kuku=malloc(1000);
	}
	for (int i=0;i<100;i++)
    {
	    kuku=malloc(1000);
	}
     kuku="hfhfhf";
	    kuku=malloc(1000);
	printf("%s",kuku);
	return 0;
}
