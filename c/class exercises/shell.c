#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMDSIZE 255
#define MAXARGS 100

int main(void)
{
	int i;
    while(1)
    {
        char input[CMDSIZE + 1];
        char *ptr = input;
        char *args[MAXARGS + 1];
		printf("Type a command: ");
        fgets(input, CMDSIZE, stdin);
        for (i = 0; i < sizeof(args) && *ptr; ptr++)
        {

            for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++);
            *ptr = '\0';
        }
        if (fork() == 0)
        {
        	exit(execvp(args[0], args));
        }
        wait(NULL);
    }
}



