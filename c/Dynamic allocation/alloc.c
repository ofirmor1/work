#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	int index;
	char *ptr, *temp;
	ptr = (char*)malloc(100*sizeof(char));
	if(ptr == NULL)
	{
		return -1;
	}
	for(index = 0; index < 100; index++)
	{
		*(ptr+index) = index+3;
		*(ptr+index) = '\0';
		printf("%d\n", *ptr+index);
	}
	printf("Original: %s", ptr);
	temp = (char*)realloc(ptr,10000000000000*sizeof(char));
	printf("ptr: %p\n", ptr);
	printf("temp: %p\n", temp);
	
	free(ptr);
	free(temp);
	
	printf("free ptr: %p\n",ptr);
	printf("free temp: %p\n",temp);
	
	return 0;
}
