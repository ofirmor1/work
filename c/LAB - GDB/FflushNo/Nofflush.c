#include <stdio.h>
#include <unistd.h>
char GlobalChar = 'G';


int main ()
{
	int MainIntLocal=-0;
    	puts("Starting program\n");
	for (int i=0;i<1024;i++)
	{
		printf("M");
//		sleep(1);
	}
//	fflush(stdout);
	sleep(10);
	getchar();
//	printf("M");
	sleep(5);
    	puts("Press enter to terminate\n");
	getchar();
	return(MainIntLocal);
}
