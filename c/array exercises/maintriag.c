#include <stdio.h>
#include "triag.h"

int main(void)
{
	int n = 6;
	char ch = '*';
	printf("\n\n\n");
	func1(n, ch);
	printf("\n\n\n");
	func2(n, ch);
	printf("\n\n\n");
	func3(n-1, ch);
	printf("\n\n\n");
	func4(n, ch);
	printf("\n\n\n");
	func5(n, ch);
	printf("\n\n\n");
	func6(n, ch);
	printf("\n\n\n");
	return 0;
}
