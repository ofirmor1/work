#include <stdio.h>
#include "triag.h"

int main(void)
{
	int n = 6;
	char ch = '*';
	func1(n, ch, 0);
	printf("\n\n");
	func2(n, ch, 0);
	printf("\n\n");
	func3(n-1, ch, 0);
	printf("\n\n");
	/*func4(n, ch);
	printf("\n\n");
	func5(n, ch);
	printf("\n\n");
	func6(n, ch);
	return 0;*/
}
