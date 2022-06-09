#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int g_var = 0;

int main()
{
	int i, j, l_var = 0;
	pid_t n;	
	sleep(10);
	n = fork();
	if( n < 0) /* fork() failed */
	{
		printf("Error fork create fail\n");
	}
	else if(n > 0) /* parent */
	{
		printf("g_var %d\n", g_var);
		printf("l_var %d\n", l_var);
		for( i = 0; i < 30; ++i)
		{
			++g_var;
			++l_var;
		}
		sleep(20);
		printf("After Loop\n");
		printf("g_var %d\n", g_var);
		printf("l_var %d\n", l_var);
	}
	else /* child */
	{
		printf("g_var %d\n", g_var);
		printf("l_var %d\n", l_var);
		for( i = 0; i < 50; ++i)
		{
			++g_var;
			++l_var;
		}
		sleep(10);
		printf("After Loop\n");
		printf("g_var %d\n", g_var);
		printf("l_var %d\n", l_var);
	}

	return 0;
}
