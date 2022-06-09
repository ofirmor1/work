#include <stdio.h>
#include <stdlib.h>
/*****************Recurse Solution***********************/
long Fib(int _num)
/*{
	if(_num== 0)
	{
		return 0;
	}
	else if(_num == 1)
	{
		return 1;
	}
	else
	{
		return Fib(_num-1)+Fib(_num-2);
	}	
		
}*/
{
	return (_num <= 1) ? _num : Fib(_num-1)+Fib(_num-2);
}
int main(void)
{
	long fib;
	fib = Fib(10);
	printf("%ld \n", fib);
	fib = Fib(40);
	printf("%ld \n", fib);
	fib = Fib(42);
	printf("%ld \n", fib);	
	
}

/*****************itterative Solution***********************/
