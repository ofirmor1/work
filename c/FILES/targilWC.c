#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	FILE *cfPtr;
	if((cfPtr = fopen("persons.txt" , "w+")) == NULL)
	{
		printf("File could not be opened \n");
	}
	else
	{
		
	}

		fclose(cfPtr);
	}
	
}
