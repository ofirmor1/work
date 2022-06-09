#include <unistd.h>
#include <stdio.h>
int main ()
{
		printf("M");
		sleep(5);
		printf("M");
		sleep(5);
		printf("M");
		sleep(5);
		printf("\n");
		sleep(5);
// no fllush
		printf("M");
		fflush(stdout);
		sleep(5);
		printf("M");
		fflush(stdout);
		sleep(5);
		printf("\n");
		fflush(stdout);
		sleep(5);
	   	puts("Press enter to terminate");
		getchar();
		return(0);
}
